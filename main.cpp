#include "Graph.h"
#include <iostream>

int main() {
	Vertex<int, int> v1(1);
	Edge<int, int> e1(&v1, 20);
	Vertex<int, int> v2(2);
	Edge<int, int> e2(&v2, 25);
	v1.Edges->insert(e1);
	v1.Edges->insert(e2);
	for (std::set<Edge<int, int>> ::iterator it = v1.Edges->begin(); it != v1.Edges->end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << e1 << std::endl;

	size_t size = 10;
	Graph<int, int> g1(size);
	if (g1.add_vertex(v1)) {
		std::cout << "Inserted" << std::endl;
	}
	if (g1.has_vertex(v1)) {
		std::cout << "g1 Has" << std::endl;
	}

	Graph<int, int> g2(g1);
	if (g2.has_vertex(v1)) {
		std::cout << "g2 Has" << std::endl;
	}
	std::cout << "Hello world" << std::endl;

	HashTable<std::string, size_t> h1(10, true);
	h1.print();

	std::cout << std::endl << std::endl << std::endl;
	for (size_t out_idx = 0; out_idx < h1.getSize(); ++out_idx) {
		std::cout << out_idx << ")";
		for (auto it = h1[out_idx].begin(); it != h1[out_idx].end(); ++it) {
			std::cout << " Data: " << *it;
		}
		std::cout << std::endl;
	}


	g1.remove_vertex(v1);

}