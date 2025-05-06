#pragma once
#include <set>
#include <C:\Users\moroz\OneDrive\Desktop\2 kurs\back\Aisdd\lab\lab3_sem4\AiSD\myHashTable\HashTable.h>

template<class Value, class Distance = double>
struct Vertex;


template<class Value, class Distance = double>
struct Edge {
	Vertex<Value, Distance>* adjacentVertex;
	Distance weight;
	Edge(Vertex<Value, Distance>* adjacentNode, Distance wight);
	bool operator<(const Edge<Value, Distance>& other) const;
};


template <class Value, class Distance = double>
struct Vertex {
	Value value;
	std::set<Edge<Value, Distance>> Edges;
	Vertex(Value value);
	Vertex();
	bool operator<(const Vertex<Value, Distance>& other) const;
	bool operator!=(const Vertex<Value, Distance>& other) const;
};

template<class Value, class Distance>
std::ostream& operator<<(std::ostream& stream,const Edge<Value, Distance>& edge);
