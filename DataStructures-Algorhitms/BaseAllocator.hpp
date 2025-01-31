#pragma once
#include "AllocatorInterface.hpp"


class BaseAllocator : public AllocatorInterface {
public:
	BaseAllocator(size_t size) 
		:chunkSize(size)
	{}
	void* allocateBlock() override {
		char* ptr = new char[chunkSize];
		return ptr;
	}

	//warning , this
	void deallocate(void* ptr) override {
		char* data = reinterpret_cast<char*>(ptr);
		delete[] data;
	}
private:
	size_t chunkSize;
};

