#include "hash/HashTableV1.h"

HashTableV1::HashTableV1(size_t tableSize) : numElements(0) {
    table.resize(tableSize);
}

uint64_t HashTableV1::hashFunction(const std::string& key) const {
    uint64_t hashValue = 0;
    for (char c : key) {
        // Polynomial rolling hash calculation
        hashValue = (hashValue * MULTIPLIER + static_cast<uint64_t>(c)) % table.size();
    }
    return hashValue;
}

void HashTableV1::insert(const std::string& key) {
    uint64_t index = hashFunction(key);
    table[index].push_back(key); // Separate chaining via std::list
    numElements++;
}

bool HashTableV1::lookup(const std::string& key) const {
    uint64_t index = hashFunction(key);
    const auto& chain = table[index];
    for (const auto& item : chain) {
        if (item == key) {
            return true;
        }
    }
    return false;
}

size_t HashTableV1::getMaxChainLength() const {
    size_t maxLength = 0;
    for (const auto& chain : table) {
        if (chain.size() > maxLength) {
            maxLength = chain.size();
        }
    }
    return maxLength;
}
