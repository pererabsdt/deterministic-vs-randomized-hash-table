#include "hash/HashTableV1.h"

HashTableV1::HashTableV1(size_t tableSize) : numElements(0) {
    table.resize(tableSize);
}

uint64_t HashTableV1::hashFunction(const std::string& key) const {
    // TODO: Implement Karp-Rabin polynomial rolling hash
    return 0; 
}

void HashTableV1::insert(const std::string& key) {
    // TODO: Implement insert with separate chaining
}

bool HashTableV1::lookup(const std::string& key) const {
    // TODO: Implement lookup
    return false; 
}

size_t HashTableV1::getMaxChainLength() const {
    // TODO: Implement calculation of max chain length
    return 0; 
}
