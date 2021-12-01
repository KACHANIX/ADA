#pragma once
#include <cassert>
#include <Windows.h>  
#include <iostream> 
#define DEBUG

class FSA
{
private:
	struct Page
	{
	public:
		Page* next;
		void* chunk;
		int fl_index;

		Page(void* chunk, Page* next = nullptr)
		{
			this->next = next;
			this->chunk = chunk;
			fl_index = -1;
		}

		void Init(void* chunk, Page* next = nullptr)
		{
			this->next = next;
			this->chunk = chunk;
			fl_index = -1;
		}
	};
	Page* pages_;
	size_t block_size_;
	size_t blocks_initiated_;
	static constexpr size_t MIN_BYTES = 16;
	size_t CHUNK_SIZE = 4096;

	enum class State
	{
		NotInitialized,
		Initialized,
		Destroyed
	};
	State state = State::NotInitialized;

public:
	FSA()
	{
		block_size_ = 0;
		blocks_initiated_ = 0;
		pages_ = nullptr;
	}

	~FSA()
	{
		assert(state != State::Destroyed);
		destroy();
	}

	FSA(const FSA&) = delete;
	FSA& operator=(const FSA&) = delete;

	void init(size_t initialSize = MIN_BYTES)
	{
		block_size_ = initialSize;
		void* new_chunk = VirtualAlloc(NULL, CHUNK_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		pages_ = static_cast<Page*>(new_chunk);
		pages_->Init(static_cast<void*>(static_cast<char*>(new_chunk) + sizeof(Page)));
		state = State::Initialized;
	}

	void destroy()
	{
		while (pages_)
		{
			auto tmp = pages_;
			pages_ = pages_->next;
			VirtualFree(tmp, 0, MEM_RELEASE);
		}
		blocks_initiated_ = 0;
	}

	void* alloc()
	{
		assert(state == State::Initialized);
		auto cur_page = pages_;
		while (cur_page && !(blocks_initiated_ < (CHUNK_SIZE - sizeof(Page)) / block_size_) && cur_page->fl_index != -1)
		{
			cur_page = cur_page->next;
		}

		// if it's full
		if (!cur_page)
		{
			void* new_chunk = VirtualAlloc(NULL, CHUNK_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			auto new_page = static_cast<Page*>(new_chunk);
			new_page->Init(static_cast<void*>(static_cast<char*>(new_chunk) + sizeof(Page)), pages_);
			pages_ = new_page;
			blocks_initiated_ = 0;
			return alloc();
		}

		// if some memory was freed
		if (cur_page->fl_index != -1)
		{
			char* temp = static_cast<char*>(cur_page->chunk) + cur_page->fl_index * block_size_;
			cur_page->fl_index = *reinterpret_cast<int*>(temp);
			return static_cast<void*>(temp);
		}
		else
		{
			char* temp = static_cast<char*>(cur_page->chunk) + blocks_initiated_ * block_size_;
			blocks_initiated_++;
			return static_cast<void*>(temp);
		}
	}

	void free(void* blockToFree)
	{
		assert(state == State::Initialized);
		auto cur_page = pages_;
		while (cur_page && !(static_cast<char*>(blockToFree) >= static_cast<char*>(cur_page->chunk)
			&& static_cast<char*>(cur_page->chunk) + CHUNK_SIZE - sizeof(Page) > static_cast<char*>(blockToFree))) 
		{
			cur_page = cur_page->next;
		}

		if (!cur_page) return;
		int distance = static_cast<char*>(blockToFree) - static_cast<char*>(cur_page->chunk);
		*static_cast<int*>(blockToFree) = cur_page->fl_index;
		cur_page->fl_index = distance / block_size_;
	}

#ifdef DEBUG
	void dumpStat() const
	{
		std::cout << "FSA " << block_size_ << " bytes:" << std::endl;
		std::cout << "\tFree: ";
		int free_count = CHUNK_SIZE / block_size_ - blocks_initiated_;
		auto cur_page = pages_;
		int all_count = cur_page ? 0 : free_count;
		while (cur_page)
		{
			all_count += CHUNK_SIZE / block_size_;
			auto fIndex = cur_page->fl_index;
			while (fIndex != -1) {
				free_count++;
				fIndex = *reinterpret_cast<int*>(static_cast<char*>(cur_page->chunk) + fIndex * block_size_);
			}
			cur_page = cur_page->next;
		}
		std::cout << free_count << std::endl;
		std::cout << "\tEngaged: " << all_count - free_count << std::endl;
	}
#endif 
};