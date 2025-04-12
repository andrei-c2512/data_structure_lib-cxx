#pragma once


namespace TinyDS{
    class AllocatorInterface {
        public:
            virtual void* allocateBlock() = 0;
            virtual void deallocate(void* ptr) = 0;
    };
}
