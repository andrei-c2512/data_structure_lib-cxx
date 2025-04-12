#pragma once
#include "AllocatorInterface.hpp"
#include "Common.hpp"

namespace TinyDS{
    class PoolAllocator : public AllocatorInterface{
    public:
            PoolAllocator( size_t chunkSize0);
            PoolAllocator(const PoolAllocator& al) = delete;
            PoolAllocator& operator=(const PoolAllocator& al) = delete;
            PoolAllocator(PoolAllocator&& al) noexcept;
            PoolAllocator& operator=(PoolAllocator&& al) noexcept;
            ~PoolAllocator();
            void* allocateBlock();
            void deallocate(void* ptr);
            void reserve(size_t chunks);
    private:
            bool validPointer(void* ptr);
    private:
            char* storagePtr;
            size_t chunkSize;
            size_t chunkIndex;
            size_t nChunks;
            std::queue<void*> freedBlocks;

    };
}
