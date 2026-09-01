#include "hash/HashTableV1.h"
#include "hash/HashTableV2.h"
#include "data/DataGenerator.h"
#include "benchmark/Benchmark.h"
#include <iostream>

int main() {
    std::cout << "Environment setup successful! Ready for development.\n";

    // Basic instantiation to ensure linking works
    HashTableV1 ht1(10);
    HashTableV2 ht2(10);
    
    std::cout << "Hash tables linked successfully.\n";
    
    return 0;
}
