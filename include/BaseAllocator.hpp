#pragma once
#include "AllocatorInterface.hpp"
#include "Common.hpp"

namespace TinyDS{
    class BaseAllocator : public AllocatorInterface { 
        public:
            BaseAllocator(size_t size);
            void* allocateBlock() override;
            void deallocate(void* ptr) override;
    private:
            size_t chunkSize;
    };
}

