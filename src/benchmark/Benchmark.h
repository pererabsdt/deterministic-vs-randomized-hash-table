#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <string>
#include <vector>

class HashTableV1;
class HashTableV2;

struct BenchmarkResult {
    std::string testName;
    size_t tableSize;
    size_t dataSize;
    double insertTimeMs;
    double lookupTimeMs; // time for 1000 lookups
    size_t maxChainLength;
};

class Benchmark {
public:
    static BenchmarkResult runV1(const std::string& testName, const std::vector<std::string>& dataset, size_t tableSize, const std::vector<std::string>& lookupKeys);
    static BenchmarkResult runV2(const std::string& testName, const std::vector<std::string>& dataset, size_t tableSize, const std::vector<std::string>& lookupKeys);
    
    static void saveToCSV(const std::vector<BenchmarkResult>& results, const std::string& filename);
};

#endif // BENCHMARK_H
