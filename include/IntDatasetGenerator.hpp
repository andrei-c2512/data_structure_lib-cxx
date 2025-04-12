#pragma once
#include <random>
#include <vector>


namespace TinyDS{
    class IntDatasetGenerator {
    public:
            IntDatasetGenerator();
            std::vector<int> generate(size_t size, int32_t lowerBounds, int32_t upperBounds);
    private:
            std::random_device rd;
            std::mt19937 rng;
            std::uniform_int_distribution<int32_t> range;
    };
}
