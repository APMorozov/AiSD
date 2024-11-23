#include "Polynom.h"
#include <random>
#include <iostream>
template<class T>

Polynom<T>::Polynom(const size_t max_degree) {
	if (max_degree < 0) {
		throw std::logic_error("Max degree must be > 0");
	}
	else {
		T* vector = new T[max_degree + 1]();
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
Polynom<T> :: ~Polynom() {
	
	delete[] _coef;
}


template<class T>
Polynom<T> ::Polynom(Polynom<T>& item) {
	T* newcoef = new T[item._size](T{});
	for (size_t idx = 0; idx < item._size; ++idx) {
		newcoef[idx] = item[idx];
	}
	_coef = newcoef;
	_size = item._size;
}

template<class T>
T& Polynom<T> :: operator[](size_t idx) const{
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
size_t Polynom<T> :: get_size() const{
	return _size;
}


template<class T>
Polynom<T>& Polynom<T> :: operator+=(Polynom<T>& first) {
	size_t max_size = (_size > first._size) ? _size : first._size;
	T* newcoef = new T[max_size]();
	T c1;
	T c2;
	for (size_t idx = 0; idx < max_size; ++idx) {
		c1 = (idx > _size) ? T{} : _coef[idx];
		c2 = (idx > first._size) ? T{} : first[idx];
		newcoef[idx] = c1 + c2;
	}
	delete[] _coef;
	_coef = newcoef;
	_size = max_size;
	return *this;
}

template<class T>
Polynom<T>& Polynom<T> :: operator-=(Polynom<T>& first) {
	size_t max_size = (_size > first._size) ? _size : first._size;
	T* newcoef = new T[max_size]();
	T c1;
	T c2;
	for (size_t idx = 0; idx < max_size; ++idx) {
		c1 = (idx > _size) ? T{} : _coef[idx];
		c2 = (idx > first._size) ? T{} : first[idx];
		newcoef[idx] = c1 - c2;
	}
	delete[] _coef;
	_coef = newcoef;
	_size = max_size;
	return *this;
}

template<class T>
Polynom<T> operator+(Polynom<T> first, Polynom<T>& second) {
	return first+=second;
}

template<class T>
Polynom<T> operator-(Polynom<T> first, Polynom<T>& second) {
	return first-=second;
}

template<class T>
Polynom<T>& Polynom<T> :: operator*=(T scalar) {
	for (size_t idx = 0; idx < _size; ++idx) {
		_coef[idx] *= scalar;
	}
	return *this;
}

template<class T>
Polynom<T>& operator*(T scalar, Polynom<T>& item) {
	item *= scalar;
	return item;
}

template<class T>
Polynom<T>& Polynom<T> :: operator=(const Polynom<T>& first) {
	if (*this == first) {
		return *this;
	}
	T* newcoef = new T[first._size]();
	for (size_t idx = 0; idx < first._size; ++idx) {
		newcoef[idx] = first[idx];
	}
	 delete[] _coef;
	_coef = newcoef;
	_size = first._size;
	return *this;
}
template<class T>
bool Polynom<T>::operator==(const Polynom<T>& other) const {
	if (_size != other._size) return false;

	for (size_t i = 0; i <= _size; ++i) {
		if (std::fabs(_coef[i] - other[i]) > EPS) return false;
	}

	return true;
}

template<class T>
bool Polynom<T>::operator!=(const Polynom<T>&other) const
{
	return !(*this == other);
}

template<class T>
Polynom<T>& operator*(Polynom<T>& item, T scalar) {
	item *= scalar;
	return item;
}

template<class T>
void Polynom<T> ::shrink_to_fit() {
	size_t idx = _size;
	while (_coef[idx-1] == T(0)) {
		--idx;
	}

	if (idx == _size) {
		throw std::logic_error("Polynom have only empty elm");
	}
	std::cout << "LEN zeros " << idx << '\n';
	if (idx != 0) {
		T* newcoef = new T[idx]();
		for (size_t i = 0; i < idx; ++i) {
			newcoef[i] = _coef[i];
		}
		_size = idx;
		delete[] _coef;
		_coef = newcoef;
	}
}


template<class T>
void Polynom<T> :: expend(int size){
	if (size <= _size) {
		throw std::logic_error("Can`t expend, sizes ara Equal");
	}
	T* newcoef = new T[size]();
	for (size_t idx = 0; idx < _size; ++idx) {
		newcoef[idx] = _coef[idx];
	}
	delete[] _coef;
	_coef = newcoef;
	_size = size;
}

template<class T>
std::ostream& operator<<(std::ostream& stream,const Polynom<T>& item) {
	for (size_t idx = 0; idx < item.get_size(); ++idx) {
		stream << item[idx] << ' ';
	}
	return stream;
}

template<class T>
T Polynom<T> :: compute_polynom(T x) {
	T result{};
	for (size_t idx = 0; idx < _size; ++idx) {
		result += _coef[idx] * T(pow(x, idx));
	}
	return result;
}


