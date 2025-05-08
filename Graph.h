#pragma once
#include <set>
#include <list>
#include <iostream>
#include "HashTable.h"  // Используйте относительные пути

template<class Value, class Distance = double>
struct Vertex;

template<class Value, class Distance = double>
struct Edge {
    Vertex<Value, Distance>* adjacentVertex;
    Distance weight;
    Edge(Vertex<Value, Distance>* adjacentNode, Distance wight)
        : adjacentVertex(adjacentNode), weight(wight) {
    }

    bool operator<(const Edge<Value, Distance>& other) const {
        if (this->adjacentVertex != other.adjacentVertex)
            return this->adjacentVertex < other.adjacentVertex;
        return this->weight < other.weight;
    }
};

template <class Value, class Distance = double>
struct Vertex {
    Value value;
    std::set<Edge<Value, Distance>>* Edges;

    Vertex(Value val) : value(val), Edges(new std::set<Edge<Value, Distance>>{}) {}
    Vertex() : value(0), Edges(new std::set<Edge<Value, Distance>>{}) {}

    bool operator<(const Vertex<Value, Distance>& other) const {
        return this->value < other.value;
    }

    bool operator!=(const Vertex<Value, Distance>& other) const {
        return this->value != other.value;
    }
    bool operator==(const Vertex<Value, Distance>& other) const {
        return this->value == other.value;
    }
};

template<class Value, class Distance>
std::ostream& operator<<(std::ostream& stream, const Edge<Value, Distance>& edge) {
    stream << "Weight: " << edge.weight << " AdjacentVertex: " << edge.adjacentVertex->value;
    return stream;
}

template<class Value, class Distance>
class Graph {
private:
    HashTable<Value, Vertex<Value, Distance>, std::list<Node<Value, Vertex<Value, Distance>>>> _verteces;
public:
    Graph(): _verteces(15){}

    Graph(size_t size): _verteces(size){}

    ~Graph() = default;

    Graph(const Graph<Value, Distance>& other) = default;

    bool has_vertex(const Vertex<Value, Distance>& vertex) const{
       return this->_verteces.contains(vertex);
    }

    bool add_vertex(const Vertex<Value, Distance>& vertex) {
        if (this->has_vertex(vertex)) {
            return false;
        }
        this->_verteces.insert(vertex.value, vertex);
        return true;
    }

    bool remove_vertex(const Vertex<Value, Distance>& vertex) {
        if (this->has_vertex(vertex)) {

        }
    }
};