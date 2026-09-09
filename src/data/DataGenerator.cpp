#include "data/DataGenerator.h"
#include "../lib/rapidcsv-9.07/rapidcsv.h"
#include <random>
#include <string>

void DataGenerator::generateBenignData(size_t size, size_t length) {
    std::vector<std::string> dataset;
    dataset.reserve(size);
    // Random alphanumeric string generation
    
    std::random_device rd;
    std::mt19937 generator(rd());    
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() -1);
    
    // Generating random strings
    for(size_t i = 0 ; i< size;i++){
        std::string random_string;
        random_string.reserve(length);
        for (size_t j = 0; j < length; ++j) {
            random_string += CHARACTERS[distribution(generator)];
        }
        dataset.push_back(random_string);
    }

    // Saving random strings to .csv file
    const std::string outputPath = "alph_num.csv";
    rapidcsv::Document doc("", rapidcsv::LabelParams(-1, -1)); // No headers / row labels
    doc.SetColumn(0, dataset);
    doc.Save(outputPath);
}

 std::vector<std::string> DataGenerator::generateAdversarialData(size_t numPairs) {
    std::vector<std::string> dataset;
    
    // For V1, Hash(s) = (...(s[0]*31 + s[1])*31 + s[2]...)
    // Two strings with the exact same polynomial evaluation: "Aa" and "BB"
    // 'A' (65) * 31 + 'a' (97) = 2015 + 97 = 2112
    // 'B' (66) * 31 + 'B' (66) = 2046 + 66 = 2112
    // By generating all combinations of these two chunks, we get 2^numPairs strings
    // that are mathematically guaranteed to have the same exact hash in V1.
    std::string s1 = "Aa";
    std::string s2 = "BB";
    
    size_t totalElements = 1ULL << numPairs; // 2^numPairs
    dataset.reserve(totalElements);
    
    for (size_t i = 0; i < totalElements; ++i) {
        std::string s;
        s.reserve(numPairs * 2);
        for (size_t bit = 0; bit < numPairs; ++bit) {
            if ((i >> bit) & 1) {
                s += s2;
            } else {
                s += s1;
            }
        }
        dataset.push_back(s);
    }
    
    return dataset;
}
