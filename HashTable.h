#pragma once
#include <iostream>
#include <list>
#include <random>
#include <algorithm>

size_t normal_dist(size_t begin, size_t end) {
    if (end < begin) {
        throw "end must be > begin";
    }
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> dist(begin, end);
    return dist(e);
}

template<class Key, class Value>
struct Node {
    Key key;
    Value value;
    Node(Key key, Value value) : key(key), value(value) {}
};

template<class Key, class Value>
std::ostream& operator<<(std::ostream& stream, const Node<Key, Value>& elm) {
    stream << elm.key << " : " << elm.value;
    return stream;
}

template<class Key, class Value>
bool operator==(const Node<Key, Value>& lhs, const Node<Key, Value>& rhs) {
    return (lhs.key == rhs.key) && (lhs.value == rhs.value);
}

template<class Key, class Value, class Container = std::list<Node<Key, Value>>>
class HashTable {
private:
    Container* _buckets;
    size_t _current_size;
    size_t _default_size;

public:
    HashTable() : _buckets(nullptr), _current_size(0), _default_size(0) {}

    HashTable(size_t size) : _current_size(0), _default_size(size) {
        _buckets = new Container[size]{};
    }

    HashTable(const HashTable& table) : _buckets(nullptr), _current_size(0), _default_size(0) {
        if (this != &table) {
            _buckets = new Container[table._default_size];
            _current_size = table._current_size;
            _default_size = table._default_size;
            for (size_t i = 0; i < table._default_size; ++i) {
                for (const auto& other_it : table._buckets[i]) {
                    _buckets[i].push_back(Node<Key, Value>(other_it.key, other_it.value));
                }
            }
        }
    }

    HashTable(size_t size, bool is_random) : _current_size(0), _default_size(size) {
        if constexpr (std::is_same_v<Key, std::string> && std::is_same_v<Value, size_t>) {
            _buckets = new Container[size]{};
            size_t begin_ascii = 32;
            size_t end_ascii = 126;

            for (size_t i = 0; i < size; ++i) {
                size_t str_len = normal_dist(1, 30);
                size_t node_value = normal_dist(1, 500);
                std::string str;

                for (size_t j = 0; j < str_len - 1; ++j) {
                    size_t idx = normal_dist(begin_ascii, end_ascii);
                    str += static_cast<char>(idx);
                }

                size_t index = pirsonHash(str, size);
                _buckets[index].push_back(Node<Key, Value>(str, node_value));
                _current_size++;
            }
        }
        else {
            throw "ERROR! Key must be std::string and Value must be size_t for random initialization";
        }
    }

    ~HashTable() {
        if (_buckets != nullptr) {
            delete[] _buckets;
        }
    }

    size_t shiftHash(const Key key) const {
        if constexpr (std::is_same_v<Key, std::string>) {
            size_t hash = 0;
            for (auto ch : key) {
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

    size_t pirsonHash(std::string& s, size_t tableSize) const {
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

        unsigned char h = 0;
        for (int j = 0; j < 8; ++j) {
            h = T[(s[0] + j) % 256];
            for (int i = 1; i < s.size(); ++i) {
                h = T[h ^ s[i]];
            }
        }
        return h % tableSize;
    }

    bool insert(Key key, const Value& value) {
        size_t index = shiftHash(key);
        for (const auto& it : _buckets[index]) {
            if (it.key == key) {
                return false;
            }
        }
        _buckets[index].push_back(Node<Key, Value>(key, value));
        _current_size++;
        return true;
    }

    void print() const {
        for (size_t i = 0; i < _default_size; ++i) {
            std::cout << i << ") ";
            for (const auto& it : _buckets[i]) {
                std::cout << it << " ";
            }
            std::cout << '\n';
        }
    }

    void insert_or_assign(Key key, Value value) {
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

    bool contains(const Value& value) const {
        for (size_t i = 0; i < _default_size; ++i) {
            for (const auto& it : _buckets[i]) {
                if (it.value == value) {
                    return true;
                }
            }
        }
        return false;
    }

    Value* search(Key key) {
        size_t index = shiftHash(key);
        for (auto& it : _buckets[index]) {
            if (it.key == key) {
                return &it.value;
            }
        }
        return nullptr;
    }

    bool erase(Key key) {
        size_t index = shiftHash(key);
        auto& container = _buckets[index];
        auto it = std::find_if(
            container.begin(),
            container.end(),
            [&key](const Node<Key, Value>& node) {
                return node.key == key;
            }
        );

        if (it != container.end()) {
            container.erase(it);
            _current_size--;
            return true;
        }
        return false;
    }

    size_t count(Key key) const {
        size_t index = shiftHash(key);
        return std::distance(_buckets[index].begin(), _buckets[index].end());
    }

    HashTable& operator=(const HashTable& table) {
        if (this == &table) {
            return *this;
        }

        delete[] _buckets;
        _buckets = new Container[table._default_size];
        _current_size = table._current_size;
        _default_size = table._default_size;

        for (size_t i = 0; i < _default_size; ++i) {
            for (const auto& it : table._buckets[i]) {
                _buckets[i].push_back(Node<Key, Value>(it.key, it.value));
            }
        }
        return *this;
    }

    const Container& operator[](size_t index) const{
        return _buckets[index];
    }

    size_t getSize() {
        return _default_size;
    }
};