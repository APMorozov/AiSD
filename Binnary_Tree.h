#pragma once
#include <stack>

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
	bool conteinsOrder(Tree_Node<T>* root, T value);
	Tree_Node<T>* eraseNode(Tree_Node<T>* root, T value);
	Tree_Node<T>* findMin(Tree_Node<T>* root);
	Tree_Node<T>* copyTree(Tree_Node<T>* root);
	int getHeight(Tree_Node<T>* root);
	int getBalanceFactor(Tree_Node<T>* root);
	Tree_Node<T>* rotateLeft(Tree_Node<T>* root);
	Tree_Node<T>* rotateRight(Tree_Node<T>* root);
	Tree_Node<T>* balanceNode(Tree_Node<T>* root);
	size_t getCount(Tree_Node<T>* root ,T value);
public:
	Binnary_Tree(T root);
	Binnary_Tree(Binnary_Tree<T>& Tree);
	void insert(T value);
	void print();
	bool conteins(T value);
	bool erase(T value);
	Binnary_Tree<T>& operator=(Binnary_Tree<T>& other);
	void balanceTree();
	size_t count(T value);

	class iterator {
	private:
		std::stack<Tree_Node<T>*> _stack;
		Tree_Node<T>* _current;
		void pushLeft(Tree_Node<T>* node);
	public:
		iterator(Tree_Node<T>* pointer);
		T& operator*();
		T* operator->();
		bool hasNext();
		T& next();
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;
	};
	iterator begin();
	iterator end();
};