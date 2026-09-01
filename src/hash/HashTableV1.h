#ifndef HASH_TABLE_V1_H
#define HASH_TABLE_V1_H

#include <string>
#include <vector>
#include <list>
#include <cstdint>

class HashTableV1 {
private:
    std::vector<std::list<std::string>> table;
    size_t numElements;
    
    // Fixed parameters for Karp-Rabin polynomial rolling hash
    const uint64_t MULTIPLIER = 31; 
    
public:
    HashTableV1(size_t tableSize);
    
    uint64_t hashFunction(const std::string& key) const;
    void insert(const std::string& key);
    bool lookup(const std::string& key) const;
    
    size_t getMaxChainLength() const;
    size_t getTableSize() const { return table.size(); }
    size_t getNumElements() const { return numElements; }
};

#endif // HASH_TABLE_V1_H
