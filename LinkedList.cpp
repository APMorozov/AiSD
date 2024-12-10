#include "LinkedList.h"
#include <stdexcept>
#include <string> 
#include <windows.h>
#include <fstream>
#include <locale>
#include <codecvt>
#include <cstdlib>
#include <io.h>
#include <fcntl.h>
#include <cstdlib>

template<class T>
LinkedList<T> :: LinkedList() {
	_head = nullptr;
}


template<class T>
LinkedList<T> ::LinkedList(const LinkedList<T>& elm) {
	Node<T>* next = elm._head;
	_head = nullptr;
	while ((next) != nullptr) {
		this->push_tail(*next);
		next = next->pnext;
	}
}

template<class T>
LinkedList<T> ::~LinkedList() {
	Node<T>* next = _head;
	while ((next) != nullptr) {
		this->pop_tail();
		next = next->pnext;
	}
}

template<class T>
void LinkedList<T> :: push_tail(Node<T>& elm) {
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
void LinkedList<T> ::push_tail(LinkedList<T>& elm) {
	if (_head == nullptr) {
		LinkedList<T>* newlist = new LinkedList<T>(elm);
		this->_head = newlist->_head;
	}
	else {
		LinkedList<T>* newlist = new LinkedList<T>(elm);
		Node<T>* next = _head;
		while ((next->pnext) != nullptr) {
			next = next->pnext;
		}
		next->pnext = newlist->_head;
	}
}

template<class T>
void LinkedList<T> ::push_head(Node<T>& elm) {
	if (_head == nullptr) {
		Node<T>* newhead = new Node<T>(elm.data);
		_head = newhead;
	}
	else {
		Node<T>* oldhead = _head;
		Node<T>* newhead = new Node<T>(elm.data);
		_head = newhead;
		_head->pnext = oldhead;
	}
}

template<class T>
void LinkedList<T> ::push_head(LinkedList<T>& elm) {
	if (_head == nullptr) {
		LinkedList<T>* newlist = new LinkedList<T>(elm);
		this->_head = newlist->_head;
	}
	else {
		Node<T>* oldhead = _head;
		LinkedList<T>* newhead = new LinkedList<T>(elm);
		_head = newhead ->_head;
		Node<T>* next = _head;
		while ((next->pnext) != nullptr) {
			next = next->pnext;
		}
		next->pnext = oldhead;
		
	}
}

template<class T>
void LinkedList<T> ::pop_tail() {
	if (_head == nullptr) {
		throw std::logic_error("List is empty");
	}
	else {
		Node<T>* next = _head;
		Node<T>* prenext;
		while ((next) != nullptr) {
			prenext = next;
			next = next->pnext;
		}
		delete next;
		prenext -> pnext = nullptr;
	}
}

template<class T>
void LinkedList<T> ::pop_head() {
	if (_head == nullptr) {
		throw std::logic_error("List is empty");
	}
	else {
		if ((_head->pnext) != nullptr) {
			Node<T>* next = _head->pnext;
			delete _head;
			_head = next;
		}
		else {
			delete _head;
			_head = nullptr;
		}
	}
}

template<class T>
void LinkedList<T> ::delete_node(Node<T>& del_node) {
	if (_head == nullptr) {
		throw std::logic_error("List is empty");
	}
	Node<T>* next = _head;
	Node<T>* prenext;
	while ((next) != nullptr) {
		if ((next == _head) && (next->data == del_node.data)) {
			this->pop_head();
		}
		if ((next->data == del_node.data)) {
			prenext->pnext = next->pnext;
			delete next;
			next = prenext->pnext;
		}
		else {
			prenext = next;
			next = next->pnext;
		}
	}
}

template<class T>
void LinkedList<T> ::set_by_idx(Node<T>& elm, size_t idx) {
	size_t counter = 0;
	Node<T>* next = _head;
	Node<T>* prenext = _head;
	while ((next != nullptr) && (counter != idx)) {
		prenext = next;
		next = next->pnext;
		++counter;
	}
	if (counter == 0) {
		this->push_head(elm);
	}
	else if ((counter == idx) && (next != nullptr)) {
		Node<T>* newelm = new Node<T>(elm.data);
		prenext->pnext = newelm;
		newelm->pnext = next->pnext;
	}
	else {
		throw std::logic_error("Idx out of range");
	}
}

template<class T>
Node<T>& LinkedList<T> ::get_by_idx(size_t idx) {
	size_t counter = 0;
	Node<T>* next = _head;
	while ((next != nullptr) && (counter != idx)) {
		next = next->pnext;
		++counter;
	}
	if (counter == idx) {
		return next;
	}
	else {
		throw std::logic_error("Idx out of range");
	}
}

template<class T>
LinkedList<T>& LinkedList<T> :: operator=(const LinkedList<T>& elm) {
	LinkedList<T>* newlist = new LinkedList<T>(elm);
	this->_head = newlist->_head;
	return *this;
}

template<class T>
Node<T>* LinkedList<T> :: get_head() const noexcept{
	return _head;
}


template<class T>
void LinkedList<T>::open_file() {
	std::string path;
	Node<T>* next = this->_head;
	while (next != nullptr) {
		path += next->data;
		next = next->pnext;
		if (next != nullptr) {
			path += '\\';
		}
	}
	std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<char>());
	std::ifstream infile(path);

	infile.imbue(utf8_locale);

	if (!infile) {
		std::cerr << "Cant open file!" << std::endl;
	}
	else
	{
		std::string line;
		while (std::getline(infile, line)) {
			std::cout << line << std::endl;
		}

		infile.close();
	
	}
}




