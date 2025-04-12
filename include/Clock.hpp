#pragma once
#include <chrono>
#include <iostream>
#include <string_view>

namespace TinyDS::Testing {
	class Clock {
	public:
		Clock() = default;
		void start();
		float timeElapsed() const noexcept;
		void reset();
		void stop();
		//writes a message , the time elapsed , resets and stops
		void bench(std::string_view benchName);
	private:
		std::chrono::steady_clock::time_point _start;
		float carry = 0.0f;
		bool stopped = true;
	};
}
