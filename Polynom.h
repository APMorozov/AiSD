#include <stdexcept>
template<class T>


class Polynom {
private:
	T* _coef;
	size_t _size;
public:
	Polynom(const size_t max_degree);

	Polynom(T *vector, const size_t vsize);


};