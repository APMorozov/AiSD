#pragma once
#include <iostream>

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
	LinkedList(const LinkedList<T>& elm);
	void push_tail(Node<T>& elm);
};

template<class T>
std::ostream& operator<<(std::ostream& stream,const LinkedList<T>& elm);