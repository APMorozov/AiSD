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
		_size = max_degree + 1;
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


template<class T>
size_t Polynom<T> :: get_size() {
	return _size;
}


template<class T>
Polynom<T>& Polynom<T> :: operator+=(Polynom<T>& first) {
	size_t max_size = (_size > first.get_size()) ? _size : first.get_size();
	T* newcoef = new T[max_size](T{});
	T c1;
	T c2;
	for (size_t idx = 0; idx < max_size; ++idx) {
		c1 = (idx >= _size) ? T{} : _coef[idx];
		c2 = (idx >= first.get_size()) ? T{} : first[idx];
		newcoef[idx] = c1 + c2;
	}
	delete[] _coef;
	_coef = newcoef;
	_size = max_size;
	return *this;
}

template<class T>
Polynom<T>& Polynom<T> :: operator-=(Polynom<T>& first) {
	size_t max_size = (_size > first.get_size()) ? _size : first.get_size();
	T* newcoef = new T[max_size](T{});
	T c1;
	T c2;
	for (size_t idx = 0; idx < max_size; ++idx) {
		c1 = (idx >= _size) ? T{} : _coef[idx];
		c2 = (idx >= first.get_size()) ? T{} : first[idx];
		newcoef[idx] = c1 - c2;
	}
	delete[] _coef;
	_coef = newcoef;
	_size = max_size;
	return *this;
}

template<class T>
Polynom<T>& operator+(Polynom<T>& first, Polynom<T>& second) {
	Polynom<T> sumpoly(1);
	sumpoly += first;
	sumpoly += second;
	return sumpoly;
}

template<class T>
Polynom<T>& operator-(Polynom<T>& first, Polynom<T>& second) {
	Polynom<T> sumpoly(1);
	first-=second;
	sumpoly += first;
	return sumpoly;
}

