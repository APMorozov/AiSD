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
HashTable<Key, Value, Conteiner> ::HashTable(const HashTable<Key, Value, Conteiner>& table) {
	if (this != &table) {
		_buckets = new Conteiner[table._default_size];
		_current_size = table._current_size;
		_default_size = table._default_size;
		for (size_t i{}; i < table._default_size; ++i) {
			for (auto other_it : table._buckets[i]) {
				_buckets[i].push_back(Node<Key, Value>(other_it.key, other_it.value));
			}
		}
	}
}

template<class Key, class Value, class Conteiner>
HashTable<Key, Value, Conteiner> :: ~HashTable() {
	if (_buckets != nullptr) {
		delete[] _buckets;
		_buckets = nullptr;
	}
}

template<class Key, class Value, class Conteiner>
bool HashTable<Key, Value, Conteiner> ::insert(Key key, const Value& value) {
	size_t index = shiftHash(key);
	for (auto it: _buckets[index]) {
		if (it.key == key) {
			return true;
		}
	}
	_buckets[index].push_back(Node<Key,Value>(key, value));
	_current_size++;
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


template<class Key, class Value, class Conteiner>
HashTable<Key, Value, Conteiner>& HashTable<Key, Value, Conteiner> :: operator=(const HashTable<Key, Value, Conteiner>& table) {
	if (this == &table) {
		return *this;
	}
	delete[] _buckets;
	_buckets = new Conteiner[table._default_size];
	_current_size = table._current_size;
	_default_size = table._default_size;
	for (size_t i = 0; i < _default_size; ++i) {
		for (const auto& it : table._buckets[i]) {
			_buckets[i].push_back(Node<Key, Value>(it.key, it.value));
		}
	}
	return *this;
}

template<class Key, class Value, class Conteiner>
void HashTable<Key, Value, Conteiner> ::insert_of_assign(Key key, Value& value) {
	size_t index = shiftHash(key);
	for (auto& it : _buckets[index]) {
		if (it.key == key) {
			it.value = value;
			return;
		}
	}
	_buckets[index].push_back(Node<Key, Value>(key, value));
	_current_size++;
}