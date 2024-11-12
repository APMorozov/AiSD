#include "Polynom.cpp"
#include "complex"

int main() {
	Polynom<std::complex<int>> first(5);
	std::complex<int> array[] = { 1,4,6 };
	std::cout << "Second" << '\n';
	Polynom<std::complex<int>> second(array, 3);
	first -= second;
	for (int i = 0; i < first.get_size(); ++i) {


		std::cout << first[i] << '\n';
	}
	std::cout << "len first: " << first.get_size() << '\n';
	

	Polynom<std::complex<int>> sum(3);
	sum = first - second;
	std::cout << "Sum" << '\n';
	for (int i = 0; i < first.get_size(); ++i) {


		std::cout << sum[i] << '\n';
	}


	return 0;
}