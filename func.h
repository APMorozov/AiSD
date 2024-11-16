#pragma once
#include "Polynom.cpp"
#include "complex"
#include "func.h"

template<class T>
T* find_root(Polynom<T>& item) {
	if ((item.get_size() > 3) || (item.get_size() == 1)) {
		throw std::out_of_range("Poly len must be in range (1,3] in this method");
	}
	T* answer = new T[2](T{});
	if ((item.get_size() == 1) || (item[2] == T(0))) {
		answer[0] -= item[0] / item[1];
		answer[1] -= item[0] / item[1];
	}
	else {
		T discriminant = pow(item[1], 2) - (4 * item[2] * item[0]);
		std::cout << "B^2 " << pow(item[1], 2) << '\n';
		std::cout << "4AC " << (4 * item[2] * item[0]) << '\n';
		if (discriminant > 0) {
			std::cout << "sup " << discriminant << '\n';
			T x1 = (0 - item[1] + sqrt(discriminant)) / (2 * item[2]);
			T x2 = (0 - item[1] - sqrt(discriminant)) / (2 * item[2]);
			std::cout << "x1 " << x1 << '\n';

			std::cout << "x1 " << x1 << "\n";
			std::cout << "x2 " << x2 << "\n";
			answer[0] = x1;
			answer[1] = x2;
		}
		else if (discriminant == 0) {
			T x1 = (0 - item[1]);
			answer[0] = x1;
			answer[1] = x1;
		}
		else {
			throw std::logic_error("Complex roots");
		}
	}
}

template<>
std::complex<double>* find_root(Polynom<std::complex<double>>& item) {
	if ((item.get_size() > 3) || (item.get_size() == 1)) {
		throw std::out_of_range("Poly len must be in range (1,3] in this method");
	}
	std::complex<double>* answer = new std::complex<double>[2](std::complex<double>{});
	if ((item.get_size() == 1) || (item[2] == std::complex<double>(0))) {
		answer[0] -= item[0] / item[1];
		answer[1] -= item[0] / item[1];
		return answer;
	}
	else {
		std::complex<double> discriminant = pow(item[1], 2) - (std::complex<double>(4) * item[2] * item[0]);
		std::cout << "B^2 " << pow(item[1], 2) << '\n';
		std::cout << "4AC " << (std::complex<double>(4) * item[2] * item[0]) << '\n';
		std::complex<double> x1 = (std::complex<double>(0) - item[1] + sqrt(discriminant)) / (std::complex<double>(2) * item[2]);
		std::complex<double> x2 = (std::complex<double>(0) - item[1] - sqrt(discriminant)) / (std::complex<double>(2) * item[2]);
		answer[0] = x1;
		answer[1] = x2;
		return answer;
	}
}

