#include "Benchmark.h"
#include "hash/HashTableV1.h"
#include "hash/HashTableV2.h"
#include <iostream>
#include <chrono>
#include <fstream>

using namespace std::chrono;

BenchmarkResult Benchmark::runV1(const std::string& testName, const std::vector<std::string>& dataset, size_t tableSize, const std::vector<std::string>& lookupKeys, const std::vector<std::string>& deleteKeys) {
    HashTableV1 ht(tableSize);
    
    // Measure insertion
    auto startInsert = high_resolution_clock::now();
    for (const auto& key : dataset) {
        ht.insert(key);
    }
    auto endInsert = high_resolution_clock::now();
    double insertTime = duration_cast<duration<double, std::milli>>(endInsert - startInsert).count();
    
    // Measure lookup
    auto startLookup = high_resolution_clock::now();
    for (const auto& key : lookupKeys) {
        ht.lookup(key);
    }
    auto endLookup = high_resolution_clock::now();
    double lookupTime = duration_cast<duration<double, std::milli>>(endLookup - startLookup).count();
    
    // Measure deletion
    auto startDelete = high_resolution_clock::now();
    for (const auto& key : deleteKeys) {
        ht.remove(key);
    }
    auto endDelete = high_resolution_clock::now();
    double deleteTime = duration_cast<duration<double, std::milli>>(endDelete - startDelete).count();
    
    return {testName, tableSize, dataset.size(), insertTime, lookupTime, deleteTime, ht.getMaxChainLength()};
}

BenchmarkResult Benchmark::runV2(const std::string& testName, const std::vector<std::string>& dataset, size_t tableSize, const std::vector<std::string>& lookupKeys, const std::vector<std::string>& deleteKeys) {
    HashTableV2 ht(tableSize);
    
    // Measure insertion
    auto startInsert = high_resolution_clock::now();
    for (const auto& key : dataset) {
        ht.insert(key);
    }
    auto endInsert = high_resolution_clock::now();
    double insertTime = duration_cast<duration<double, std::milli>>(endInsert - startInsert).count();
    
    // Measure lookup
    auto startLookup = high_resolution_clock::now();
    for (const auto& key : lookupKeys) {
        ht.lookup(key);
    }
    auto endLookup = high_resolution_clock::now();
    double lookupTime = duration_cast<duration<double, std::milli>>(endLookup - startLookup).count();
    
    // Measure deletion
    auto startDelete = high_resolution_clock::now();
    for (const auto& key : deleteKeys) {
        ht.remove(key);
    }
    auto endDelete = high_resolution_clock::now();
    double deleteTime = duration_cast<duration<double, std::milli>>(endDelete - startDelete).count();
    
    return {testName, tableSize, dataset.size(), insertTime, lookupTime, deleteTime, ht.getMaxChainLength()};
}

void Benchmark::saveToCSV(const std::vector<BenchmarkResult>& results, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing.\n";
        return;
    }
    
    file << "TestName,TableSize,DataSize,InsertTimeMs,LookupTimeMs,DeleteTimeMs,MaxChainLength\n";
    for (const auto& r : results) {
        file << r.testName << "," 
             << r.tableSize << "," 
             << r.dataSize << "," 
             << r.insertTimeMs << "," 
             << r.lookupTimeMs << "," 
             << r.deleteTimeMs << "," 
             << r.maxChainLength << "\n";
    }
    
    std::cout << "Results saved to " << filename << "\n";
}
