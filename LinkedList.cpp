#include "LinkedList.h"

template<class T>
LinkedList<T> ::LinkedList() {
	_head = nullptr;
}

template<class T>
void LinkedList<T> ::push_tail(Node<T>& elm) {
	if (_head == nullptr) {
		Node<T>* newelm = new Node(elm.data);
		_head = newelm;
	}
	else {
		Node<T>* next = _head;
		while ((next -> pnext) != nullptr) {
			next = next->pnext;
		}
		Node<T>* newelm = new Node(elm.data);
		next -> pnext = newelm;
	}
}

template<class T>
LinkedList<T> ::LinkedList(const LinkedList<T>& elm) {
	Node<T>* next = elm._head;
	while (next != nullptr) {
		push_tail(next);
		next = next -> pnext;
	}
}

template<class T>
Node<T>* LinkedList<T> :: get_head() const noexcept{
	return _head;
}

template<class T>
std::ostream& operator<<(std::ostream& stream, const LinkedList<T>& elm) {
	Node<T>* next = elm.get_head();
	while (next != nullptr) {
		stream << next -> data << " ";
		next = next -> pnext;
	}
	return stream;
}