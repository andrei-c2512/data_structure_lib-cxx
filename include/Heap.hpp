#pragma once
#include <queue>
#include <stack>
#include <cmath>

namespace TinyDS{
    template<typename T>
    class Heap {
    public:
            Heap() = default;
            Heap(std::vector<T> vec) {
                    list = std::move(vec);
            }

            void setList(std::vector<T> vec) {
                    list = std::move(vec);
                    //for easier calculations
                    list.insert(std::begin(list) , T());
                    list.emplace_back(T());
            }
            void maxHeapify(int32_t index) {

                    int32_t nextIndex = index;

                    while (nextIndex != -1) {
                            int32_t left = 2 * nextIndex;
                            int32_t right = 2 * nextIndex + 1;

                            int32_t largest = nextIndex;

                            if (list[largest] < list[left])
                                    largest = left;
                            if (list[largest] < list[right])
                                    largest = right;

                            if (largest == nextIndex)
                                    nextIndex = -1;
                            else
                                    std::swap(list[largest], list[nextIndex]);
                    }
            }

            void buildHeap(int end) {
                    int32_t leavesStart = end / 2 + 1;
                    for (int32_t i = leavesStart - 1; i >= 1; i--) {
                            maxHeapify(i);
                    }
            }

            void sort() {
                    int32_t i = list.size() - 2;
                    while (i != 1) {
                            buildHeap(i);
                            std::swap(list[1], list[i + 1]);
                            i--;
                    }
            }
            void print() {
                    for (const T& val : list) {
                            std::cout << val << ' ';
                    }
                    std::cout << '\n';
            }
    private:
            std::vector<T> list;
    };
}
