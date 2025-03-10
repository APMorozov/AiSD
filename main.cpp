#include "iostream"
#include "Binnary_Tree.cpp"

int main(){
	Binnary_Tree<int> Tree(23);
	std::cout << "Hello World" << '\n';
	Tree.insert(34);
	Tree.insert(55);
	Tree.insert(23);
	Tree.insert(55);
	Tree.insert(3435);
	Tree.print();
	std::cout << '\n';
	if (Tree.conteins(34)) {
		std::cout << "Yes" << '\n';
	}
	Tree.erase(55);
	Tree.erase(55);
	Tree.erase(23);
	Tree.print();
	std::cout << '\n';
	Binnary_Tree<int> Tree1(33);
	Tree1.insert(44);
	Tree1.erase(33 );
	Tree1.print();
	std::cout << '\n';
	Binnary_Tree<int> Tree2(Tree);
	Tree2.print();
	std::cout << '\n';
	Binnary_Tree<int> Tree3 = Tree1;
	Tree3.print();
	Tree3.insert(32423);
	Tree3.insert(242);
	Tree3.insert(100);
	Tree3.insert(234);
	Tree3.print();
	std::cout << '\n';
	//Tree3.balanceTree();
	Tree3.print();
	std::cout << '\n';
	Binnary_Tree<int> :: iterator current = Tree3.begin();
	for (auto it = Tree3.begin(); it.hasNext(); ) {
		std::cout << it.next() << ' ';
	}

	std::cout << '\n';
	std::cout << Tree3.count(23);
	return 0;
}