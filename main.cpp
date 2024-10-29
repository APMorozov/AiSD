#include "Polynom.cpp"
#include "complex"

int main() {
	Polynom<std::complex<double>> first(5);
	std::complex<double> array[] = { 1,4,6 };
	std::cout << "Second" << '\n';
	Polynom<std::complex<double>> second(array, 3);
	std::cout << "take elm by idx:" << '\n' << second[2]<<'\n';
	second.set(1, 60);
	std::cout << "set elm by idx:" << '\n' << second[2] << '\n';
	return 0;
}