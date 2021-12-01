#pragma once 
#include "Coalesce.h"
#include "FSA.h" 
#include <cassert>
#include <Windows.h>
#include <iostream>
#define DEBUG

size_t sizes[] = { 16, 32, 64, 128, 256, 512 };

class MemoryAllocator
{
private:
	struct Block
	{
		Block(void* chunk, size_t size, Block* next = nullptr)
		{
			this->size = size;
			this->next = next;
			this->chunk = chunk;
		}

		void Init(void* chunk, size_t size, Block* next = nullptr)
		{
			this->size = size;
			this->next = next;
			this->chunk = chunk;
		}

		Block* next;
		size_t size;
		void* chunk;
	};
	Block* blocks_ = nullptr;
	CoalesceAllocator CA_;
	FSA FSAs_[6];
	void* base_;

	MemoryAllocator(const MemoryAllocator&) = delete;
	MemoryAllocator& operator=(const MemoryAllocator&) = delete;
public:
	MemoryAllocator()
	{

	}
	~MemoryAllocator()
	{

	}
	void init()
	{
		base_ = VirtualAlloc(NULL, 1024 * 1024 * 100, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		blocks_ = nullptr;
		for (auto i = 0; i < 6; i++) {
			FSAs_[i].init(sizes[i]);
		}
		CA_.init();
	}

	void destroy()
	{
		for (auto& FSA : FSAs_)
		{
			FSA.destroy();
		}
		CA_.destroy();
		VirtualFree(base_, 0, MEM_RELEASE);
	}

	void* alloc(size_t nbytes)
	{
		void* result = nullptr;
		if (nbytes >= 10 * 1024 * 1024)
		{
			void* temp = VirtualAlloc(NULL, nbytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			auto tempBlock = reinterpret_cast<Block*>(reinterpret_cast<char*>(blocks_) + sizeof(Block) + blocks_->size);
			tempBlock->Init(temp, nbytes, blocks_);
			blocks_ = tempBlock;
			return temp;
		}
		if (nbytes >= 512)
			result = CA_.alloc(nbytes);
		else {
			for (int i = 0; i < 6; i++)
			{
				if (nbytes < sizes[i])
				{
					result = FSAs_[i].alloc();
					break;
				}
			}
		}

		if (blocks_)
		{
			auto tempBlock = reinterpret_cast<Block*>(reinterpret_cast<char*>(blocks_) + sizeof(Block) + blocks_->size);
			tempBlock->Init(result, nbytes, blocks_);
			blocks_ = tempBlock;
		}
		else
		{
			auto tempBlock = static_cast<Block*>(base_);
			tempBlock->Init(result, nbytes, blocks_);
			blocks_ = tempBlock;
		}

		return result;
	}

	void free(void* blockToFree)
	{
		auto next_block = blocks_;
		auto cur_block = blocks_;
		if (next_block->chunk != blockToFree)
		{
			while (cur_block && cur_block->next && !(static_cast<char*>(blockToFree) == static_cast<char*>(cur_block->next->chunk)))
			{
				cur_block = cur_block->next;
			}
			next_block = cur_block->next ? cur_block->next : cur_block;
		}

		if (next_block)
		{
			if (next_block->size >= 10 * 1024 * 1024)
			{
				VirtualFree(next_block->chunk, 0, MEM_RELEASE);
			}
			else if (next_block->size >= 512)
			{
				CA_.free(blockToFree);
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					if (next_block->size < sizes[i])
					{
						FSAs_[i].free(blockToFree);
						break;
					}
				}
			}
		}

		if (cur_block == next_block)
		{
			blocks_ = blocks_->next;
		}
		else if (next_block)
		{
			cur_block->next = next_block->next;
		}
	}

#ifdef DEBUG
	virtual void dumpStat() const
	{
		for (const auto& fsa : FSAs_)
		{
			fsa.dumpStat();
		}
		CA_.dumpStat();
		auto stat_blocks = blocks_;
		while (stat_blocks) {
			if (stat_blocks->size >= 10 * 1024 * 1024)
			{
				std::cout << "OC  block:" << std::endl;
				std::cout << "\tEngaged: " << stat_blocks->size << std::endl;
			}
			stat_blocks = stat_blocks->next;
		}
	}
	virtual void dumpBlocks() const
	{
		auto stat_blocks = blocks_;
		std::cout << "Dump Blocks:" << std::endl;
		while (stat_blocks)
		{
			std::cout << "\tBlock: " << (stat_blocks->chunk) << ", size " << stat_blocks->size << std::endl;
			stat_blocks = stat_blocks->next;
		}
	}
#endif
};
