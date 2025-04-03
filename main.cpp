#include <iostream>
#include <list>
#include <vector>
#include "HashTable.cpp"


int main() {
	Node<int, int> node0(1, 5);
	HashTable<int, int, std::list<Node<int, int>>> table0(10);
	HashTable<int, int, std::list<Node<int, int>>> table1;
	std::cout << "Hello " << node0;
	std::cout << '\n' << table0.shiftHash(12) << '\n';
	table0.insert(6, 34);
	table0.insert(234234233, 2234);
	table0.insert(16, 8756);
	table0.print();
	HashTable<int, int, std::list<Node<int, int>>> table2(table0);
	std::cout << "Hello " << '\n';
	table2.print();
	HashTable<std::string, int, std::vector<Node<std::string, int>>> table3(10);
	table3.insert(std::string("abba"), 345);
	table3.insert(std::string("abb432a"), 3455);
	std::cout << '\n' << table3.shiftHash("abb432a") << '\n';
	std::cout << "Hello " << '\n';
	table3.print();

	return 0;
}