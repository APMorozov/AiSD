#include "HashTable.h"
#include <typeinfo>

template<class Key, class Value>
std::ostream& operator<<(std::ostream& stream, const Node<Key, Value>& elm) {
	stream << elm.key << " : " << elm.value;
	return stream;
}

template<class Key, class Value, class Conteiner>
size_t HashTable<Key, Value, Conteiner> :: shiftHash(const Key key) {
	if constexpr (std::is_same_v<Key, std::string>) {
		size_t hash = 0;
		for (auto ch: key) {
			hash = (hash << 5) ^ ch;
		}
		return hash % _default_size;
	}
	else {
		size_t hash = static_cast<size_t>(key);
		hash = (hash << 5) ^ hash;
		return hash % _default_size;
	}
}

template<class Key, class Value, class Conteiner>
HashTable<Key, Value, Conteiner> ::HashTable() {
	_buckets = nullptr;
	_current_size = 0;
	_default_size = 0;
}

template<class Key, class Value, class Conteiner>
HashTable<Key, Value, Conteiner> ::HashTable(size_t size) {
	_buckets = new Conteiner[size]{};
	_current_size = 0;
	_default_size = size;
}

template<class Key, class Value, class Conteiner>
bool HashTable<Key, Value, Conteiner> ::insert(Key key, const Value& value) {
	size_t index = shiftHash(key);
	for (auto it: _buckets[index]) {
		if (it.key == key) {
			return true;
		}
	}
	//Node<Key, Value>* nNode = new Node(key, value);
	_buckets[index].push_back(Node<Key,Value>(key, value));
}


template<class Key, class Value, class Conteiner>
void HashTable<Key, Value, Conteiner> ::print() {
	for (size_t i{}; i < _default_size; ++i) {
		std::cout << i << ") ";
		for (auto it : _buckets[i]) {
			std::cout << it << " ";
		}
		std::cout << '\n';
	}
}