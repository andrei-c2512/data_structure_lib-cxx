#pragma once
#include <queue>
#include <assert.h>
#include "AllocatorInterface.hpp"
#include <cstdint>

class PoolAllocator : public AllocatorInterface{
public:
	PoolAllocator( size_t chunkSize0)
		:nChunks(2) , chunkSize(chunkSize0)
	{
		storagePtr = new char[2 * chunkSize];
		chunkIndex = 0;
	}
	PoolAllocator(const PoolAllocator& al) = delete;
	PoolAllocator& operator=(const PoolAllocator& al) = delete;
	PoolAllocator(PoolAllocator&& al) noexcept {
		storagePtr = al.storagePtr;
		al.storagePtr = nullptr;
		chunkSize = std::move(al.chunkSize);
		chunkIndex = std::move(al.chunkIndex);
		nChunks = std::move(al.nChunks);
	}
	PoolAllocator& operator=(PoolAllocator&& al) noexcept {
		storagePtr = al.storagePtr;
		al.storagePtr = nullptr;
		chunkSize = std::move(al.chunkSize);
		chunkIndex = std::move(al.chunkIndex);
		nChunks = std::move(al.nChunks);
		return *this;
	}
	~PoolAllocator() {
		delete[] storagePtr;
	}
	void* allocateBlock() {
		if (freedBlocks.empty()) {
			void* nextBlock = (void*)(storagePtr + chunkIndex * chunkSize);
			assert(validPointer(nextBlock));
			chunkIndex++;
			return nextBlock;
		}
		else {
			void* nextBlock = freedBlocks.front();
			freedBlocks.pop();
			return nextBlock;
		}
	}
	void deallocate(void* ptr) {
		assert(validPointer(ptr));
		freedBlocks.emplace(ptr);
		memset(ptr, 0, chunkSize);
	}
	//TO DO: make it work even if you have data in it.
	void reserve(size_t chunks) {
		delete[] storagePtr;
		nChunks = chunks;
		chunkIndex = 0;
		storagePtr = new char[chunks * chunkSize];
	}
private:
	bool validPointer(void* ptr) {
		return ptr >= (void*)storagePtr && ptr < (void*)(storagePtr + chunkSize * nChunks);
	}
private:
	char* storagePtr;
	size_t chunkSize;
	size_t chunkIndex;
	size_t nChunks;
	std::queue<void*> freedBlocks;

};