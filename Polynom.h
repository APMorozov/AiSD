#include <stdexcept>
template<class T>


class Polynom {
private:
	T* _coef;
	size_t _size;
public:
	Polynom(const size_t max_degree);

	Polynom(T *vector, const size_t vsize);

	T& operator[](size_t idx);

	void set(const T elm, const size_t idx);

	size_t get_size();

	Polynom& operator+=(Polynom<T>& firsrt);

	Polynom& operator-=(Polynom<T>& first);


};


template<class T>
Polynom<T>& operator+(Polynom<T>& first, Polynom<T>& second);
template<class T>
Polynom<T>& operator-(Polynom<T>& first, Polynom<T>& second);