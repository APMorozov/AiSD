#pragma once
#include "Polynom.cpp"
#include <complex>


template<class T>
T* find_root(Polynom<T>& item) {
	if ((item.get_size() > 3) || (item.get_size() == 1)) {
		throw std::out_of_range("Poly len must be in range (1,3] in this method");
	}
	T* answer = new T[2](T{});
	if ((item.get_size() == 1) || (item[2] == T(0))) {
		answer[0] -= item[0] / item[1];
		answer[1] -= item[0] / item[1];
		return answer;
	}
	else {
		T discriminant = pow(item[1], 2) - (4 * item[2] * item[0]);
		if (discriminant > 0) {
			T x1 = (0 - item[1] + sqrt(discriminant)) / (2 * item[2]);
			T x2 = (0 - item[1] - sqrt(discriminant)) / (2 * item[2]);

			answer[0] = x1;
			answer[1] = x2;
			return answer;
		}
		else if (discriminant == 0) {
			T x1 = (0 - item[1]) / (2 * item[2]);
			answer[0] = x1;
			answer[1] = x1;
			return answer;
		}
		else {
			throw std::logic_error("only complex roots");
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
		std::complex<double> x1 = (std::complex<double>(0) - item[1] + sqrt(discriminant)) / (std::complex<double>(2) * item[2]);
		std::complex<double> x2 = (std::complex<double>(0) - item[1] - sqrt(discriminant)) / (std::complex<double>(2) * item[2]);
		answer[0] = x1;
		answer[1] = x2;
		return answer;
	}
}

template<>
std::complex<float>* find_root(Polynom<std::complex<float>>& item) {
	if ((item.get_size() > 3) || (item.get_size() == 1)) {
		throw std::out_of_range("Poly len must be in range (1,3] in this method");
	}
	std::complex<float>* answer = new std::complex<float>[2](std::complex<float>{});
	if ((item.get_size() == 1) || (item[2] == std::complex<float>(0))) {
		answer[0] -= item[0] / item[1];
		answer[1] -= item[0] / item[1];
		return answer;
	}
	else {
		std::complex<float> discriminant = (item[1] * item[1]) - (std::complex<float>(4) * item[2] * item[0]);
		std::complex<float> x1 = (std::complex<float>(0) - item[1] + sqrt(discriminant)) / (std::complex<float>(2) * item[2]);
		std::complex<float> x2 = (std::complex<float>(0) - item[1] - sqrt(discriminant)) / (std::complex<float>(2) * item[2]);
		answer[0] = x1;
		answer[1] = x2;
		return answer;
	}
}

template<>
std::complex<int>* find_root(Polynom<std::complex<int>>& item) {
	if ((item.get_size() > 3) || (item.get_size() == 1)) {
		throw std::out_of_range("Poly len must be in range (1,3] in this method");
	}
	std::complex<int>* answer = new std::complex<int>[2](std::complex<int>{});
	if ((item.get_size() == 1) || (item[2] == std::complex<int>(0))) {
		answer[0] -= item[0] / item[1];
		answer[1] -= item[0] / item[1];
		return answer;
	}
	else {
		std::complex<int> discriminant = (item[1] * item[1]) - (std::complex<int>(4) * item[2] * item[0]);
		std::complex<int> x1 = (std::complex<int>(0) - item[1] + sqrt(discriminant)) / (std::complex<int>(2) * item[2]);
		std::complex<int> x2 = (std::complex<int>(0) - item[1] - sqrt(discriminant)) / (std::complex<int>(2) * item[2]);
		answer[0] = x1;
		answer[1] = x2;
		return answer;
	}
}

