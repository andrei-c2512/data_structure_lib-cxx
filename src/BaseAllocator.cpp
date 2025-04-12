#include "BaseAllocator.hpp"


namespace TinyDS{
    BaseAllocator::BaseAllocator(size_t size) 
            :chunkSize(size)
    {}
    void* BaseAllocator::allocateBlock(){
            char* ptr = new char[chunkSize];
            return ptr;
    }

    //warning , this
    void BaseAllocator::deallocate(void* ptr) {
            char* data = reinterpret_cast<char*>(ptr);
            delete[] data;
    }
}

