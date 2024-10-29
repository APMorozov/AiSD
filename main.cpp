#include "Polynom.cpp"
#include "complex"

int main() {
	Polynom<std::complex<double>> first(5);
	std::complex<double> array[] = { 1,4,6 };
	std::cout << "Second" << '\n';
	Polynom<std::complex<double>> second(array, 3);
	return 0;
}