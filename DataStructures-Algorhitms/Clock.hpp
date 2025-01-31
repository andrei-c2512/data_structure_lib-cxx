#pragma once
#include <chrono>
#include <iostream>

namespace Testing {
	class Clock {
	public:
		Clock() = default;
		void start() {
			_start = std::chrono::steady_clock::now();
			stopped = false;
		}
		float timeElapsed() const noexcept {
			if (stopped) return 0.0f;

			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<float> duration = end - _start;
			return duration.count();
		}
		void reset() {
			_start = std::chrono::steady_clock::now();
			carry = 0.0f;
		}
		void stop() {
			carry += timeElapsed();
			stopped = true;
		}
		//writes a message , the time elapsed , resets and stops
		void bench(std::string_view benchName) {
			std::cout << benchName << " -- Duration: " << timeElapsed() << '\n';
			reset();
			stop();
		}
	private:
		std::chrono::steady_clock::time_point _start;
		float carry = 0.0f;
		bool stopped = true;
	};
}
