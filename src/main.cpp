#include "data/DataGenerator.h"
#include "benchmark/Benchmark.h"
#include "lib/rapidcsv-9.07/rapidcsv.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int main() {
    std::cout << "Starting Hash Table Security & Performance Analysis...\n";

    const size_t TABLE_SIZE = 100003; // Prime table size
    const size_t NUM_PAIRS = 17; // 2^17 = 131072 adversarial strings
    const size_t LOOKUP_SIZE = 1000;

    const std::string AVALANCHE_SEED = "HelloWorld";
    
    // 1. Generate benign data  (writes to alph_num.csv)
    // We adjust count and length to match the adversarial payload for a fair comparison
    size_t count = 1ULL << NUM_PAIRS; 
    size_t length = 32;
    std::cout << "Generating benign dataset (N = " << count << ")...\n";
    DataGenerator::generateBenignData(count, length);
    
    // 2. Load benign data from the CSV file back into memory
    std::vector<std::string> benignData;
    try {
        rapidcsv::Document doc("alph_num.csv", rapidcsv::LabelParams(-1, -1));
        benignData = doc.GetColumn<std::string>(0);
    } catch (const std::exception& e) {
        std::cerr << "Failed to load alph_num.csv: " << e.what() << "\n";
        return 1;
    }
    
    // 3. Generate adversarial data
    std::cout << "Generating adversarial dataset (N = " << (1ULL << NUM_PAIRS) << ")...\n";
    auto adversarialData = DataGenerator::generateAdversarialData(NUM_PAIRS);
   
    // 4. Generate avalancheData
    std::cout <<"Generating avalanch dataset (N = "<< (1ULL << NUM_PAIRS) <<")...\n";
    std::vector<std::string> avalancheData =  DataGenerator::generateAvalancheData(
        NUM_PAIRS,
        AVALANCHE_SEED 
    );

    // 5. Select 1000 random elements for lookup from each dataset
    std::vector<std::string> benignLookupKeys;
    std::vector<std::string> adversarialLookupKeys;
    std::vector<std::string> avalancheLookupKeys;
    
    std::sample(benignData.begin(), benignData.end(), std::back_inserter(benignLookupKeys),
                LOOKUP_SIZE, std::mt19937{std::random_device{}()});
                
    std::sample(adversarialData.begin(), adversarialData.end(), std::back_inserter(adversarialLookupKeys),
                LOOKUP_SIZE, std::mt19937{std::random_device{}()});

    std::sample(avalancheData.begin(), avalancheData.end(), std::back_inserter(avalancheLookupKeys),
        LOOKUP_SIZE, std::mt19937(std::random_device{}())
    );

    std::vector<BenchmarkResult> results;

    // 6. Run Benchmarks on both datasets for V1
    std::cout << "\n--- Running V1 (Deterministic Karp-Rabin) ---\n";
    results.push_back(Benchmark::runV1("V1_Benign", benignData, TABLE_SIZE, benignLookupKeys, benignLookupKeys));
    std::cout << "V1 Benign - Max Chain Length: " << results.back().maxChainLength << "\n";
    
    results.push_back(Benchmark::runV1("V1_Adversarial", adversarialData, TABLE_SIZE, adversarialLookupKeys, adversarialLookupKeys));
    std::cout << "V1 Adversarial - Max Chain Length: " << results.back().maxChainLength << " (Expected ~65536)\n";

    results.push_back(Benchmark::runV1("V1_avalanche",avalancheData,TABLE_SIZE,avalancheLookupKeys, avalancheLookupKeys));
    std::cout << "V1 Avalanche - Max Chain Length: " << results.back().maxChainLength << "\n";

    // 7. Run Benchmarks on both datasets for V2
    std::cout << "\n--- Running V2 (Randomized Universal Hashing) ---\n";
    results.push_back(Benchmark::runV2("V2_Benign", benignData, TABLE_SIZE, benignLookupKeys, benignLookupKeys));
    std::cout << "V2 Benign - Max Chain Length: " << results.back().maxChainLength << "\n";
    
    results.push_back(Benchmark::runV2("V2_Adversarial", adversarialData, TABLE_SIZE, adversarialLookupKeys, adversarialLookupKeys));
    std::cout << "V2 Adversarial - Max Chain Length: " << results.back().maxChainLength << "\n";

    results.push_back(Benchmark::runV2("V2_Avalanche",avalancheData, TABLE_SIZE, avalancheLookupKeys, avalancheLookupKeys));
    std::cout << "V2 Avalanche - Max Chain Length: " << results.back().maxChainLength << "\n";
    
    // 7. Asymptotic Degradation testing (Running with different N to plot O(1) vs O(n))
    std::cout << "\n--- Running Asymptotic Degradation Tests ---\n";
    std::vector<size_t> sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    
    for (size_t n : sizes) {
        if (n > adversarialData.size()) continue;
        
        std::vector<std::string> subset(adversarialData.begin(), adversarialData.begin() + n);
        
        std::vector<std::string> lookupSubset;
        std::sample(subset.begin(), subset.end(), std::back_inserter(lookupSubset),
                    std::min(n, LOOKUP_SIZE), std::mt19937{std::random_device{}()});
                    
        results.push_back(Benchmark::runV1("V1_Degradation", subset, TABLE_SIZE, lookupSubset, lookupSubset));
        results.push_back(Benchmark::runV2("V2_Degradation", subset, TABLE_SIZE, lookupSubset, lookupSubset));
    }

    std::cout << "\nSaving results to benchmark_results.csv...\n";
    Benchmark::saveToCSV(results, "benchmark_results.csv");
    
    std::cout << "Experiment completed successfully!\n";
    return 0;
}
