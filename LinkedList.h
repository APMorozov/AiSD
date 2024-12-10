#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <type_traits>

template<class T>
struct Node {
	T data;
	Node<T>* pnext;
	Node(T data, T* pnext): data(data), pnext(pnext){}
	Node(T data) : data(data), pnext(nullptr) {}
};



template<class T>
class LinkedList {
private:
	Node<T>* _head;
public:
	Node<T>* get_head() const noexcept;
	LinkedList();
	LinkedList(size_t size) {
		if constexpr (std::is_integral<T>::value) {
			size_t counter = 0;
			_head = new Node<int>(rand());
			++counter;
			while (counter != size) {
				int elm_data = rand();
				Node<int> elm(elm_data);
				this->push_tail(elm);
				++counter;
			}
		}
		else {
			_head = nullptr;
		}
	}
	~LinkedList();
	LinkedList(const LinkedList<T>& elm);
	void push_tail(Node<T>& elm);
	void push_tail(LinkedList<T>& elm);
	void push_head(Node<T>& elm);
	void push_head(LinkedList<T>& elm);
	void pop_tail();
	void pop_head();
	void delete_node(Node<T>& del_elm);
	void set_by_idx(Node<T>& elm, size_t idx);
	Node<T>& get_by_idx(size_t idx);
	LinkedList<T>& operator=(const LinkedList<T>& elm);
	void open_file();
	friend std::ostream& operator<<(std::ostream& stream, const LinkedList<T>& elm) {
		Node<T>* next = elm._head;
		if (next != nullptr) {
			stream << next->data << " ";
			next = next->pnext;
		}
		while ((next != nullptr) && (next != elm._head)) {
			stream << next->data << " ";
			next = next->pnext;
		}
		return stream;
	}
};
