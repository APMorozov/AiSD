#include <iostream>
#include <list>
#include "HashTable.cpp"


int main() {
	Node<int, int> node0(1, 5);
	HashTable<int, int, std::list<Node<int, int>>> table0(10);
	HashTable<int, int, std::list<Node<int, int>>> table1();
	std::cout << "Hello " << node0;
	std::cout << '\n' << table0.shiftHash(12) << '\n';
	table0.insert(6, 34);
	table0.insert(234234233, 2234);
	table0.insert(16, 8756);
	table0.print();



	return 0;
}