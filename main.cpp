#include "Graph.cpp"
#include <iostream>

int main() {
	Vertex<int, int> v1(1);
	Edge<int, int> e1(&v1, 20);
	Vertex<int, int> v2(2);
	Edge<int, int> e2(&v2, 25);
	v1.Edges.insert(e1);
	v1.Edges.insert(e2);
	for (std::set<Edge<int, int>> ::iterator it = v1.Edges.begin(); it != v1.Edges.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << e1 << std::endl;

	std::cout << "Hello world" << std::endl;
}