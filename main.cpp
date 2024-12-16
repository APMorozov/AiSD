#include "funcs.cpp"
#include <random>
#include <iostream>
#include <vector>

int main() {
	std::random_device rd;
	std::mt19937 gen(rd());
	for (size_t i = 0; i < 100; ++i) {
		std::cout << gen() << '\n';
	}
	std::cout << "Vector" << '\n';
	std::vector<int> vec(10);
	set_random(vec, 10, gen);
	for (size_t i = 0; i < 10; ++i) {
		std::cout << vec[i] << '\n';
	}
	Stats stats1;
	stats1 = selection_sort(vec, 10);
	std::cout << "Comparations: " << stats1.comparison_count << '\n' << "Copy count: " << stats1.copy_count << '\n';
	for (size_t i = 0; i < 10; ++i) {
		std::cout << vec[i] << '\n';
	}

}