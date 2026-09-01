#ifndef HASH_TABLE_V2_H
#define HASH_TABLE_V2_H

#include <string>
#include <vector>
#include <list>
#include <cstdint>

class HashTableV2 {
private:
    std::vector<std::list<std::string>> table;
    size_t numElements;
    
    // Universal hashing parameters
    uint64_t a;
    uint64_t b;
    uint64_t p; // Large prime number
    
    // Helper to convert string to an integer < p
    uint64_t stringToInt(const std::string& key) const;

public:
    HashTableV2(size_t tableSize);
    
    uint64_t hashFunction(const std::string& key) const;
    void insert(const std::string& key);
    bool lookup(const std::string& key) const;
    
    size_t getMaxChainLength() const;
    size_t getTableSize() const { return table.size(); }
    size_t getNumElements() const { return numElements; }
};

#endif // HASH_TABLE_V2_H
