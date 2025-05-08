#include <typeinfo>
#include <random>

size_t normal_dist(size_t begin, size_t end) {
	if (end < begin) {
		throw "end must be > begin";
	}
	else {
		std::random_device r;
		std::default_random_engine e(r());
		std::uniform_int_distribution<int> dist(begin, end);
		size_t random_number = dist(e);
		return random_number;
	}
}


template<class Key, class Value>
std::ostream& operator<<(std::ostream& stream, const Node<Key, Value>& elm) {
	stream << elm.key << " : " << elm.value;
	return stream;
}

template<class Key, class Value>
bool operator ==(const Node<Key, Value>& lhs, const Node<Key, Value>& rhs) {
	if ((lhs.key == rhs.key) && (lhs.value == rhs.value)) {
		return true;
	}
	else {
		return false;
	}
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
size_t HashTable<Key, Value, Conteiner> ::pirsonHash(std::string& s, size_t tableSize) {
	if constexpr (std::is_same_v<Key, std::string>) {
		unsigned char h;
		static const unsigned char T[256] = {
			 98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219,
			 61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115,
			 90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10,
			237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121,
			123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55,
			 59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222,
			197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186,
			 39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99,
			154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254,
			133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139,
			189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44,
			183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12,
			221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166,
			  3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117,
			238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110,
			 43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239
		};
		size_t code = 0;
		for (int j = 0; j < 8; ++j) {
			h = T[(s[0] + j) % 256];
			for (int i = 1; i < s.size(); ++i) {
				h = T[h ^ s[i]];
			}
		}
		return h % tableSize;
	}
	else {
		throw "Key must by string";
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
	_buckets = nullptr;
	_current_size = 0;
	_default_size = 0;
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
HashTable<Key, Value, Conteiner> ::HashTable(size_t size, bool is_random) {
	if constexpr (std::is_same_v<Key, std::string> && std::is_same_v<Value, size_t>) {
		size_t begin_ascii = 32;
		size_t end_ascii = 126;
		_current_size = 0;
		_default_size = size;
		_buckets = new Conteiner[size]{};
		for (size_t i{}; i < size; ++i) {
			size_t str_len = normal_dist(1, 30);
			size_t node_value = normal_dist(1, 500);
			std::string str;
			for (size_t j{}; j < str_len-1; ++j) {
				size_t idx = normal_dist(begin_ascii, end_ascii);
				char ch = (char)idx;
				str += ch;
			}
			size_t index = pirsonHash(str, size);
			_buckets[index].push_back(Node<Key, Value>(str, node_value));
			_current_size++;
		}
	}
	else {
		throw "ERROR!Key must be std::string";
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

template<class Key, class Value, class Conteiner>
bool HashTable<Key, Value, Conteiner> ::conteins(Value& value) {
	for (int i{}; i < _default_size; ++i) {
		for (auto it : _buckets[i]) {
			if (it.value == value) {
				return true;
			}
		}
	}
	return false;
}

template<class Key, class Value, class Conteiner>
Value* HashTable<Key, Value, Conteiner> ::search(Key key) {
	size_t index = shiftHash(key);
	for (auto& it : _buckets[index]) {
		if (it.key == key) {
			return &it.value;
		}
	}
	return nullptr;
}


template<class Key, class Value, class Conteiner>
bool HashTable<Key, Value, Conteiner> ::erase(Key key) {
	size_t index = shiftHash(key);
	auto& container = _buckets[index];
	auto it = std::find_if(
		container.begin(),
		container.end(),
		[&key](const Node<std::string, int>& node) {
			return node.key == key;
		}
	);

	if (it != container.end()) {
		container.erase(it);
		_current_size -= 1;
		return true;
	}
	return false;
}

template<class Key, class Value, class Conteiner>
int HashTable<Key, Value, Conteiner> ::count(Key key) {
	size_t index = shiftHash(key);
	return end(_buckets[index]) - begin(_buckets[index]); 
}