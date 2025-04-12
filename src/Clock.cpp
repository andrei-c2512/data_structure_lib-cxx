#include "Clock.hpp"

namespace TinyDS::Testing{
    void Clock::start() {
            _start = std::chrono::steady_clock::now();
            stopped = false;
    }
    float Clock::timeElapsed() const noexcept {
            if (stopped) return 0.0f;

            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<float> duration = end - _start;
            return duration.count();
    }
    void Clock::reset() {
            _start = std::chrono::steady_clock::now();
            carry = 0.0f;
    }
    void Clock::stop() {
            carry += timeElapsed();
            stopped = true;
    }
    //writes a message , the time elapsed , resets and stops
    void Clock::bench(std::string_view benchName) {
            std::cout << benchName << " -- Duration: " << timeElapsed() << '\n';
            reset();
            stop();
    }
}
