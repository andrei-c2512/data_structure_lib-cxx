#pragma once
#include <queue>
#include <assert.h>

class PoolAllocator {
public:
	PoolAllocator(size_t chunks, size_t chunkSize0)
		:nChunks(chunks) , chunkSize(chunkSize0)
	{
		storagePtr = new char[chunks * chunkSize];
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
	void deallocate(void* ptr, size_t size) {
		assert(validPointer(ptr));
		freedBlocks.emplace(ptr);
		memset(ptr, 0, size);
	}

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