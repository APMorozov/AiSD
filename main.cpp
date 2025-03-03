#include "iostream"
#include "Binnary_Tree.cpp"

int main(){
	Binnary_Tree<int> Tree(23);
	std::cout << "Hello World" << '\n';
	Tree.insert(34);
	Tree.insert(55);
	Tree.print();
}