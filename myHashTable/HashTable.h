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
public:
	size_t pirsonHash(std::string& x, size_t tableSize);
	size_t shiftHash(const Key key);
	HashTable();
	HashTable(size_t size);
	HashTable(const HashTable& table);
	HashTable(size_t size, bool is_random);
	~HashTable();
	bool insert(Key key, const Value& value);
	void print();
	void insert_of_assign(Key key, Value& value);
	bool conteins(Value& value);
	Value* search(Key key);
	bool erase(Key key);
	int count(Key key);
	HashTable& operator=(const HashTable& table);

};

template<class Key, class Value>
std:: ostream& operator<<(std::ostream& stream, const Node<Key, Value>& elm);

template<class Key, class Value>
bool operator==(const Node<Key, Value>& lhs, const Node<Key, Value>& rhs);