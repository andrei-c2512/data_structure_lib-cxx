#pragma once


class AllocatorInterface {
public:
	virtual void* allocateBlock() {
		return nullptr;
	}
	virtual void deallocate(void* ptr) {}
};