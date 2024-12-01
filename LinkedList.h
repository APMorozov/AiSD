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
};

template<class T>
std::ostream& operator<<(std::ostream& stream,const LinkedList<T>& elm);