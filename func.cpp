#include "HashTable.cpp"
#include <string>


std::string readStr() {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }

bool comparisonStrHash(size_t oldHash, size_t sizeOldHashTable) {
    std::string newStr;
    HashTable<std::string, size_t, std::list<Node<std::string, size_t>>> table;
    newStr = readStr();
    size_t newHash = table.pirsonHash(newStr, sizeOldHashTable);
    if (oldHash == newHash) {
        return true;
    }
    else {
        return false;
    }
}

