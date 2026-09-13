#include "hash/HashTableV2.h"
#include <random>

// Using 2^31 - 1 as our prime. It is strictly greater than our table size
// and ensures that (a * x) fits securely inside a standard 64-bit integer without overflow.
const uint64_t LARGE_PRIME = 2147483647ULL; 

HashTableV2::HashTableV2(size_t tableSize) : numElements(0), p(LARGE_PRIME) {
    table.resize(tableSize);
    
    // Initialize random parameters 'a' and 'b' using std::mt19937_64
    std::random_device rd;
    std::mt19937_64 gen(rd());
    
    std::uniform_int_distribution<uint64_t> distA(1, p - 1);
    std::uniform_int_distribution<uint64_t> distB(0, p - 1);
    
    a = distA(gen);
    b = distB(gen);
}

uint64_t HashTableV2::stringToInt(const std::string& key) const {
    uint64_t val = 0;
    for (char c : key) {
        // Evaluate the string as a polynomial base-256 modulo p
        val = (val * 256 + static_cast<uint8_t>(c)) % p;
    }
    return val;
}

uint64_t HashTableV2::hashFunction(const std::string& key) const {
    uint64_t x = stringToInt(key);
    // Universal hash function: ((a*x + b) mod p) mod m
    uint64_t hashVal = (a * x + b) % p;
    return hashVal % table.size();
}

void HashTableV2::insert(const std::string& key) {
    uint64_t index = hashFunction(key);
    table[index].push_back(key); // Separate chaining via std::list
    numElements++;
}

bool HashTableV2::lookup(const std::string& key) const {
    uint64_t index = hashFunction(key);
    const auto& chain = table[index];
    for (const auto& item : chain) {
        if (item == key) {
            return true;
        }
    }
    return false;
}

bool HashTableV2::remove(const std::string& key) {
    uint64_t index = hashFunction(key);
    auto& chain = table[index];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (*it == key) {
            chain.erase(it);
            numElements--;
            return true;
        }
    }
    return false;
}

size_t HashTableV2::getMaxChainLength() const {
    size_t maxLength = 0;
    for (const auto& chain : table) {
        if (chain.size() > maxLength) {
            maxLength = chain.size();
        }
    }
    return maxLength;
}
