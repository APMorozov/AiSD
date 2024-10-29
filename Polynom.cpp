#include "Polynom.h"
#include <random>
#include <iostream>
template<class T>

Polynom<T>::Polynom(const size_t max_degree) {
	if (max_degree < 0) {
		throw std::logic_error("Max degree must be > 0");
	}
	else {
		T* vector = new T[max_degree + 1](T{});
		_coef = vector;
		_size = max_degree;
		for (size_t idx = 0; idx <= max_degree; ++idx) {
			std::cout << _coef[idx] << '\n';
		}
	}
}


template<class T>
Polynom<T>::Polynom(T *vector, const size_t vsize) {
	if (vsize <= 0) {
		throw std::logic_error("Polinom wust have at least 1 element");
	}
	else {
		_coef = new T[vsize];
		_size = vsize;
		for (size_t idx = 0; idx < vsize; ++idx) {
			_coef[idx] = vector[idx];
			std::cout << _coef[idx] << '\n';
		}
	}

}

template<class T>
T& Polynom<T> :: operator[](size_t idx) {
	if (idx < 0 || idx > _size) {
		throw std::logic_error("Idx out of range");
	}
	else {
		return _coef[idx];
	}
}

template<class T>
void Polynom<T> :: set(const T elm, const size_t idx) {
	if (idx < 0 || idx > _size) {
		throw std::logic_error("Idx out of range");
	}
	else {
		_coef[idx] = elm;
	}
}



