#pragma once
#include <iostream>

template<class Key, class Value>
struct Node {
	Key key;
	Value value;
	Node(Key key, Value value): key(key), value(value){}
};

template<class Key, class Value, class Conteiner>
class HashTable {
private:
	Conteiner* _buckets;
	size_t _current_size;
	size_t _default_size;
	//size_t shiftHash(const Key key);
public:
	size_t shiftHash(const Key key);
	HashTable();
	HashTable(size_t size);
	HashTable(const HashTable& table);
	~HashTable();
	bool insert(Key key, const Value& value);
	void print();
	void insert_of_assign(Key key, Value& value);
	bool conteins(Value& value);
	HashTable& operator=(const HashTable& table);

};

template<class Key, class Value>
std:: ostream& operator<<(std::ostream& stream, const Node<Key, Value>& elm);
