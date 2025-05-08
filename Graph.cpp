//#include "Graph.h"

template <class Value, class Distance>
Vertex<Value, Distance> ::Vertex(Value value) {
	this->value = value;
	this->Edges = new std::set<Edge<Value, Distance>>{};
}

template <class Value, class Distance>
Vertex<Value, Distance> ::Vertex() {
	this->value = 0;
	this->Edges = new std::set<Edge<Value, Distance>>{};
}

template <class Value, class Distance>
bool Vertex<Value, Distance>:: operator<(const Vertex<Value, Distance>& other) const {
	return this->value < other.value;
}

template <class Value, class Distance>
bool Vertex<Value, Distance>:: operator!=(const Vertex<Value, Distance>& other) const {
	return this->value != other.value;
}

template<class Value, class Distance>
Edge<Value, Distance> ::Edge(Vertex<Value,Distance>* adjacentNode, Distance weight) {
	this->adjacentVertex = adjacentNode;
	this->weight = weight;
}

template<class Value, class Distance>
bool Edge<Value, Distance> :: operator<(const Edge<Value, Distance>& other) const {
	if (this->adjacentVertex != other.adjacentVertex) return this->adjacentVertex < other.adjacentVertex;
	return this->weight < other.weight;
}

template<class Value, class Distance>
std::ostream& operator<<(std::ostream& stream,const Edge<Value, Distance>& edge) {
	stream << "Weight: " << edge.weight << " AdjacentVertex: " << edge.adjacentVertex;
	return stream;
}

template<class Value, class Distance>
Graph<Value, Distance>::Graph(size_t size) {
	this->Verteces = new HashTable<Value,Vertex<Value,Distance>, std::list<Node<Value, Vertex<Value,Distance>>>>(size);
}