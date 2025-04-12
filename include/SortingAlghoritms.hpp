#pragma once
#include <vector>
#include <stack>

namespace TinyDS::Algorhitms {
	template<typename Value , typename Comparison>
	void insertionSort(std::vector<Value>& list, Comparison c) {
		for (size_t i = 1; i < list.size(); i++) {
			int32_t j = i - 1;
			Value temp = list[i];
			while (j >= 0 && c(list[j] , list[i]) == false) {
				list[j + 1] = list[j];
				j--;
			}
			list[j + 1] = temp;
		}
	}
	
	template<typename Value , typename Comparison>
	void selectionSort(std::vector<Value>& list, Comparison c) {
		for (size_t i = 0; i < list.size(); i++) {
			size_t best = i;
			for (size_t j = i + 1; j < list.size(); j++) {
				if (c(list[j], list[best])) {
					best = j;
				}
			}
			std::swap(list[best], list[i]);
		}
	}
	template<typename Value, typename Comparison>
	void quickSort(std::vector<Value>& list, Comparison c) {
		if (list.size() <= 1)
			return;

		typedef std::pair<size_t, size_t> Interval;
		std::stack<Interval> stack;
		stack.emplace(std::make_pair(0, list.size() - 1));

		while (stack.empty() == false) {
			Interval interval = stack.top();
			stack.pop();

			size_t left = interval.first;
			size_t right = interval.second - 1;

			size_t pivot = (interval.first + interval.second ) / 2;

			std::swap(list[interval.second], list[pivot]);

			while (left < right) {
				while (left < interval.second && list[left] <= list[interval.second]) {
					left++;
				}
				while (right > interval.first && list[right] >= list[interval.second]) {
					right--;
				}
				if(left < right)
					std::swap(list[left], list[right]);
			}

			std::swap(list[left], list[interval.second]);

			if (left - interval.first > 1) {
				stack.emplace(std::make_pair(interval.first, left - 1));
			}

			if (interval.second - left > 1) {
				stack.emplace(std::make_pair(left + 1, interval.second));
			}
		}
	}
}
