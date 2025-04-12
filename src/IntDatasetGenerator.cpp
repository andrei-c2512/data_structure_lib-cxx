#include "IntDatasetGenerator.hpp"

namespace TinyDS{
    IntDatasetGenerator::IntDatasetGenerator() {
        rng = std::mt19937{ rd() };
    }
    std::vector<int> IntDatasetGenerator::generate(size_t size, int32_t lowerBounds, int32_t upperBounds) {
            range = std::uniform_int_distribution<int32_t>(lowerBounds, upperBounds);
            std::vector<int32_t> dataSet(size);

            for (int32_t& data : dataSet) {
                    data = range(rng);
            }
            return dataSet;
    }
}

