#pragma once

template<class T>
struct Tree_Node {
	T data;
	size_t duplicates_count;
	Tree_Node<T>* LeftBranch;
	Tree_Node<T>* RightBranch;
	Tree_Node(T value);
};

template<class T>
class Binnary_Tree {
private:
	Tree_Node<T>* _root;
	Tree_Node<T>* insertNode(Tree_Node<T>* root, T value);
	void printInOrder(Tree_Node<T>* root);
public:
	Binnary_Tree(T root);
	void insert(T value);
	void print();
};