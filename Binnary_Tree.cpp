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
		for (size_t i = root->duplicates_count + 1; i != 0; --i) {
			std::cout << root->data << " ";
		}
		printInOrder(root->RightBranch);
	}
}

template<class T>
void Binnary_Tree<T> :: print() {
	printInOrder(_root);
}

template<class T>
bool Binnary_Tree<T> ::conteinsOrder(Tree_Node<T>* root, T value) {
	if (root == nullptr) {
		return false;
	}
	if (value < root->data) {
		return conteinsOrder(root->LeftBranch, value);
	}
	else if (value > root->data) {
		return conteinsOrder(root->RightBranch, value);
	}
	else {
		return true;
	}
}

template<class T>
bool Binnary_Tree<T>::conteins(T value) {
	return conteinsOrder(_root, value);
}

template<class T>
Tree_Node<T>* Binnary_Tree<T> ::findMin(Tree_Node<T>* root) {
	Tree_Node<T>* tmp = root;
	while (tmp->LeftBranch != nullptr) {
		tmp = tmp->LeftBranch;
	}
	return tmp;
}

template<class T>
Tree_Node<T>* Binnary_Tree<T>::eraseNode(Tree_Node<T>* root, T value) {
	if (root == nullptr) {
		return root;
	}
	if (value < root->data) {
		root->LeftBranch = eraseNode(root->LeftBranch, value);
	}else if (value > root->data) {
		root->RightBranch = eraseNode(root->RightBranch, value);
	}
	else {
		if ((root->LeftBranch == nullptr) && (root->RightBranch == nullptr)) {
			if (root->duplicates_count == 0) {
				delete root;
				return nullptr;
			}
			else{
				root->duplicates_count -= 1;
				return root;
			}
		}else if ((root->LeftBranch == nullptr)) {
			if (root->duplicates_count == 0) {
				Tree_Node<T>* tmp = root->RightBranch;
				delete root;
				return tmp;
			}
			else {
				root->duplicates_count -= 1;
				return root;
			}
		}else if (root->RightBranch == nullptr) {
			if (root->duplicates_count == 0) {
				Tree_Node<T>* tmp = root->LeftBranch;
				delete root;
				return tmp;
			}
			else {
				root->duplicates_count -= 1;
				return root;
			}
		}
		else {
			if (root->duplicates_count == 0) {
				Tree_Node<T>* temp = findMin(root->RightBranch);
				root->data = temp->data;
				root->RightBranch = eraseNode(root->RightBranch, temp->data);
			}
			else {
				root->duplicates_count -= 1;
				return root;
			}
		}
		
	}

	return root;
}

template<class T>
bool Binnary_Tree<T> ::erase(T value) {
	if (conteins(value)) {
		_root = eraseNode(_root, value);
		return true;
	}
	else {
		return false;
	}
}


template<class T>
Tree_Node<T>* Binnary_Tree<T> :: copyTree(Tree_Node<T>* root) {
	if (root == nullptr) {
		return nullptr;
	}
	Tree_Node<T>* newNode = new Tree_Node<T>(root->data);
	newNode->LeftBranch = copyTree(root->LeftBranch);
	newNode->RightBranch = copyTree(root->RightBranch);

	return newNode;
}

template<class T>
Binnary_Tree<T> ::Binnary_Tree(Binnary_Tree<T>& Tree) {
	_root = copyTree(Tree._root);

}

template<class T>
Binnary_Tree<T>& Binnary_Tree<T> :: operator=(Binnary_Tree<T>& other) {
	Binnary_Tree(other);
	_root = other._root;
}

template<class T>
int Binnary_Tree<T> ::getHeight(Tree_Node<T>* root) {
	if (root == nullptr) {
		return 0;
	}
	return std::max(getHeight(root->LeftBranch), getHeight(root->RightBranch)) + 1;
}


template<class T>
int Binnary_Tree<T> ::getBalanceFactor(Tree_Node<T>* root) {
	if (root == nullptr) {
		return 0;
	}
	return getHeight(root->LeftBranch) - getHeight(root->RightBranch);
}

template<class T>
Tree_Node<T>* Binnary_Tree<T> ::rotateLeft(Tree_Node<T>* root) {
	Tree_Node<T>* temp = root->RightBranch;
	root->RightBranch = temp->LeftBranch;
	temp->LeftBranch = root;
	return temp;
}

template<class T>
Tree_Node<T>* Binnary_Tree<T> ::rotateRight(Tree_Node<T>* root) {
	Tree_Node<T>* temp = root->LeftBranch;
	root->LeftBranch = temp->RightBranch;
	temp->RightBranch = root;
	return temp;
}

template<class T>
Tree_Node<T>* Binnary_Tree<T> ::balanceNode(Tree_Node<T>* root) {
	if (root == nullptr) {
		return root;
	}
	int balanceFactor = getBalanceFactor(root);
	if (balanceFactor > 1) {
		if (getHeight(root->LeftBranch->LeftBranch) >= getHeight(root->LeftBranch->RightBranch){
			root = rotateRight(root);
		}
		else {
			root->LeftBranch = rotateLeft(root->LeftBranch);
			root = rotateRight(root);
		}
	}
	else if (balanceFactor < -1) {
		if (getHeight(root->RightBranch->RightBranch) >= getHeight(root->RightBranch->LeftBranch)) {
			root = rotateLeft(root);
		}
		else {
			root->RightBranch = rotateRight(root->RightBranch);
			root = rotateLeft(root);
		}
	}

	return root;
}

template<class T>
void Binnary_Tree<T>::balanceTree() {
	_root = balanceNode(_root);
}




