#include "Binnary_Tree.h"
#include "stdexcept"
#include "iostream"

template<class T>
Tree_Node<T>:: Tree_Node(T value) {
	data = value;
	duplicates_count = 0;
	LeftBranch = nullptr;
	RightBranch = nullptr;
}

template<class T>
Binnary_Tree<T> ::Binnary_Tree(T root) {
	Tree_Node<T>* new_root= new Tree_Node(root);
	_root = new_root;
}


template<class T>
Tree_Node<T>* Binnary_Tree<T> ::insertNode(Tree_Node<T>* root, T value) {
	if (root == nullptr) {
		return new Tree_Node(value);
	}
	if (value < root->data) {
		root->LeftBranch = insertNode(root->LeftBranch, value);
	}
	if (value > root->data) {
		root->RightBranch = insertNode(root->RightBranch, value);
	}
	if (value == root->data) {
		root->duplicates_count += 1;
	}

	return root;
}

template<class T>
void Binnary_Tree<T> ::insert(T value) {
	_root = insertNode(_root, value);
}

template<class T>
void Binnary_Tree<T> :: printInOrder(Tree_Node<T>* root) {
	if (root != nullptr) {
		printInOrder(root->LeftBranch);
		std::cout << root->data << " ";
		printInOrder(root->RightBranch);
	}
}

template<class T>
void Binnary_Tree<T> ::print() {
	printInOrder(_root);
}
