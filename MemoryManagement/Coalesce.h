#pragma once
#include <cassert>
#include <Windows.h>
#include <iostream> 
#define DEBUG

class CoalesceAllocator {
private:
	struct Page {
	public:
		Page* next;
		void* chunk;

		Page(void* chunk, Page* next = nullptr) {
			this->next = next;
			this->chunk = chunk;
		}
		void Init(void* chunk, Page* next = nullptr) {
			this->next = next;
			this->chunk = chunk;
		}
	};
	struct DataBlock
	{
	public:
		DataBlock* next;
		DataBlock* prev;
		size_t size;
		DataBlock(size_t size) {
			this->size = size;
		}
	};
	size_t MIN_BYTES = sizeof(DataBlock);
	size_t BUFFER = 1024 * 1024 * 10;

	Page* pages_;
	DataBlock* free_list_;

	size_t engaged_blocks_;
	size_t engaged_size_;

#ifndef NDEBUG
	enum class State
	{
		NotInitialized,
		Initialized,
		Destroyed
	};
	State state_ = State::NotInitialized;
#endif

public:
	CoalesceAllocator() {
		pages_ = nullptr;
		engaged_blocks_ = 0;
		engaged_size_ = 0;
	}

	~CoalesceAllocator()
	{
		assert(state_ != State::Destroyed);
		destroy();
	}

	CoalesceAllocator(const CoalesceAllocator&) = delete;
	CoalesceAllocator& operator=(const CoalesceAllocator&) = delete;

	void init() {
		void* newChunk = VirtualAlloc(NULL, BUFFER, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		pages_ = static_cast<Page*>(newChunk);
		pages_->Init(static_cast<void*>(static_cast<char*>(newChunk) + sizeof(Page)));
		free_list_ = static_cast<DataBlock*>(newChunk);
		free_list_->size = BUFFER - sizeof(Page);
		free_list_->next = nullptr;
		free_list_->prev = nullptr;
	}

	void destroy() {
		while (pages_) {
			auto tmp = pages_;
			pages_ = pages_->next;
			VirtualFree(tmp, 0, MEM_RELEASE);
		}
	}

	void* alloc(size_t size) {
		size_t save_size = size;
		size += sizeof(size_t);
		size += (8 - size % 8);

		size = size < MIN_BYTES ? MIN_BYTES : size;

		DataBlock* first = nullptr;
		for (auto i = free_list_; i; i = i->next) {
			if (i->size >= size) {
				first = i;
				break;
			}
		}

		// if enough memory in page
		if (first) {
			if (first->size - size < MIN_BYTES)
			{
				size = first->size;
			}
			// 
			if (first->size - size != 0) {
				auto rest = reinterpret_cast<DataBlock*>(reinterpret_cast<char*>(first) + size);
				rest->next = first->next;
				rest->prev = first->prev;
				rest->size = first->size - size;
				if (first->next)
				{
					first->next->prev = rest;
				}
				if (first->prev)
				{
					first->prev->next = rest;
				}
				if (first == free_list_)
				{
					free_list_ = rest;
				}
			}
			else {
				if (first->next)
				{
					first->next->prev = first->prev;
				}
				if (first->prev)
				{
					first->prev->next = first->next;
				}
				if (first == free_list_)
				{
					free_list_ = first->next;
				}
			}
			auto mem = static_cast<DataBlock*>(first) + 1;
			engaged_blocks_++;
			engaged_size_ += size;
			return static_cast<void*>(mem);
		}
		else {
			void* newChunk = VirtualAlloc(NULL, BUFFER, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			pages_ = static_cast<Page*>(newChunk);
			auto temp = free_list_;
			free_list_ = static_cast<DataBlock*>(newChunk);
			free_list_->size = BUFFER - sizeof(Page);
			free_list_->next = temp;
			temp->prev = free_list_;

			return alloc(save_size);
		}
	}

	void free(void* blockToFree) {
		blockToFree = static_cast<void*>(static_cast<DataBlock*>(blockToFree) - 1);
		size_t size = (static_cast<DataBlock*>(blockToFree))->size;
		DataBlock* next = nullptr;
		DataBlock* prev = nullptr;
		for (auto i = free_list_; i; i = i->next) {
			if (reinterpret_cast<char*>(i) + i->size == static_cast<char*>(blockToFree))
			{
				prev = i;
			}
			if (reinterpret_cast<char*>(i) == static_cast<char*>(blockToFree) + size)
			{
				next = i;
			}
		}

		if (prev) {
			prev->size += size;
			if (next) {
				prev->size += size;
				if (next->prev)
				{
					next->prev->next = next->next;
				}
				if (next->next)
				{
					next->next->prev = next->prev;
				}
				if (free_list_ == next)
				{
					free_list_ = next->next;
				}
			}
		}
		else if (next) {
			static_cast<DataBlock*>(blockToFree)->next = next->next;
			static_cast<DataBlock*>(blockToFree)->prev = next->prev;
			static_cast<DataBlock*>(blockToFree)->size += next->size;
			if (next->prev)
			{
				next->prev->next = static_cast<DataBlock*>(blockToFree);
			}
			if (next->next)
			{
				next->next->prev = static_cast<DataBlock*>(blockToFree);
			}
			if (free_list_ == next)
			{
				free_list_ = static_cast<DataBlock*>(blockToFree);
			}
		}
		else {
			static_cast<DataBlock*>(blockToFree)->next = free_list_;
			static_cast<DataBlock*>(blockToFree)->prev = nullptr;
			static_cast<DataBlock*>(blockToFree)->size += size;
			if (static_cast<DataBlock*>(blockToFree)->next)
			{
				static_cast<DataBlock*>(blockToFree)->next->prev = static_cast<DataBlock*>(blockToFree);
			}
			free_list_ = static_cast<DataBlock*>(blockToFree);
		}
		engaged_blocks_--;
		engaged_size_ -= size;
	}

#ifdef DEBUG
	void dumpStat() const {
		std::cout << "CA " << BUFFER << " bytes:" << std::endl;
		std::cout << "\tEngaged size: " << engaged_size_ << std::endl;
		std::cout << "\tEngaged: " << engaged_blocks_ << std::endl;
	}
#endif
};