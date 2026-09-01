#include "hash/HashTableV2.h"

const uint64_t LARGE_PRIME = 2305843009213693951ULL; // 2^61 - 1

HashTableV2::HashTableV2(size_t tableSize) : numElements(0), p(LARGE_PRIME) {
    table.resize(tableSize);
    
    // TODO: Initialize random parameters 'a' and 'b' using std::mt19937_64
}

uint64_t HashTableV2::stringToInt(const std::string& key) const {
    // TODO: Implement string to large integer conversion
    return 0; 
}

uint64_t HashTableV2::hashFunction(const std::string& key) const {
    // TODO: Implement Universal hash function: ((a*x + b) mod p) mod m
    return 0; 
}

void HashTableV2::insert(const std::string& key) {
    // TODO: Implement insert with separate chaining
}

bool HashTableV2::lookup(const std::string& key) const {
    // TODO: Implement lookup
    return false; 
}

size_t HashTableV2::getMaxChainLength() const {
    // TODO: Implement calculation of max chain length
    return 0; 
}
