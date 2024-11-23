#include "func.h"
#include <complex>

int main() {
	int arr1[] = { 1,4,2,0,0 };
	int arr2[] = { 2,3,4,0,4 };
	std::complex<double> arr3[] = {2,3,6,7,9};
	std::complex<double> arr4[] = { 3,6,8,0,4 };
	Polynom<int> first(arr1,5);
	Polynom<int> second(arr2, 5);
	Polynom <std::complex<double>> third(arr3, 5);
	Polynom <std::complex<double>> fourth(arr4, 5);
	std::cout << "First(int): " << first << '\n';
	std::cout << "Seconf(int): " << second << '\n';
	std::cout << "Thrid(complex-double) : " << third << '\n';
	std::cout << "Fourth(complex-double) : " << fourth << '\n';

	Polynom<int> Coef(5);
	std::cout << '\n' << "CTOR by max coef(5) : " << Coef << '\n';

	Coef.set(4, 3);
	std::cout << '\n' << "Method set 4 on 4th idx,  on object Coef: " << Coef << '\n';

	std::cout << '\n' << "Sum of poly" << '\n';
	std::cout << "first + second (int): " << first + second << '\n';
	std::cout << "thrid + fourth (complex-double): " << third + fourth << '\n';
	std::cout << "Difference of poly" << '\n';
	std::cout << "first - second (int): " << first - second << '\n';
	std::cout << "thrid - fourth (complex-double): " << third - fourth << '\n';
	
	std::cout << '\n' << "Multiply poly on scalar" << '\n';
	std::cout << "first * 4 (int): " << first * 4 << '\n';
	std::cout << "4 * first (int): " << first * 4 << '\n';
	std::cout << "thrid * -2 (complex-double): " << third * std::complex<double>(-2) << '\n';

	std::cout << '\n' << "Compute poly by x" << '\n';
	std::cout << "Value poly first by x = 2: " << first.compute_polynom(2) << '\n';

	std::cout << '\n' << "shrink_to_fit()" << '\n';
	Coef.shrink_to_fit();
	std::cout << "Coef.shrink_to_fit() " << Coef << '\n';


	std::cout << '\n' << "Find roots poly" << '\n';
	double* answr1;
	double array[] = { 2,5,2 };
	Polynom<double> Find(array, 3);
	answr1 = find_root(Find);
	std::cout << "Roots first" << '\n' << "First root: " << answr1[0] << '\n' << "Second root: " << answr1[1] << '\n';
	std::cout << "Compute poly by root from func find_root: " << Find.compute_polynom(answr1[0]) << '\n';


	return 0;
}