#pragma once


namespace MemoryUtility {
	constexpr size_t calculatePadding(size_t dataSize) {
		size_t cap = 1;
		while (cap < dataSize) {
			cap *= 2;
		}
		return cap - dataSize;
	}
}