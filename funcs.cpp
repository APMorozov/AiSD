#pragma once
#include <random>

struct Stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};


template<class T>
Stats selection_sort(T& arr, size_t len) {
	Stats Stat;
	for (size_t i = 0; i < len; ++i) {
		size_t min_idx = i;
		for (size_t j = i + 1; j < len; ++j) {
			Stat.comparison_count += 1;
			if (arr[min_idx] > arr[j]) {
				min_idx = j;
			}
		}
		if (i != min_idx) {
			std :: swap(arr[i], arr[min_idx]);
			Stat.copy_count += 3;
		}
	}
	return Stat;
}

template<class T>
void set_random(T& arr, size_t len, std::mt19937& gen) {
	for (size_t i = 0; i < len; ++i) {
		arr[i] = gen();
	}
}