
#include "func.h"
#include "complex"

int main() {
	Polynom<std::complex<int>> first(5);
	//first.set(std::complex<int>(4),4);
	std::complex<int> array[] = { 0,0,1,4,6 };
	std::cout << "Second" << '\n';
	Polynom<std::complex<int>> first2(array, 5);
	first2.shrink_to_fit();
	std::cout << "LEn " << first2.get_size() << '\n';
	for (int i = 0; i < first2.get_size(); ++i) {


		std::cout << first2[i] << '\n';
	}

	std::cout << "New first" << "\n";
	first2.expend(5);
	for (int i = 0; i < first2.get_size(); ++i) {


		std::cout << first2[i] << '\n';
	}
	first2 = first2 * std::complex<int>(4);
	std::cout << "New first" << "\n";
	for (int i = 0; i < first2.get_size(); ++i) {


		std::cout << first2[i] << '\n';
	}
	std::cout << '\n';
	std::complex<int> value2 = std::complex<int>(1);
	std::complex<int> value;
	//std::cout << first2.compute_polynom(value2) << '\n';

	//std::cout << "Value" << std::complex<int>(1) << '\n';

	double arr[] = { 2, 6 , 1 };
	Polynom<double> poly(arr, 3);
	double* answ;
	answ = find_root(poly);
	std::cout << answ[0] << '\n';
	std::cout << answ[1] << '\n';
	std::cout << "Compute pole " << '\n' << poly.compute_polynom(answ[1]) << '\n';
	std::cout << "Test " << 4 / 2 << '\n';
	


	return 0;
}