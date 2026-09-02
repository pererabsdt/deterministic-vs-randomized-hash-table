#include "data/DataGenerator.h"
#include <random>
#include <string>

std::vector<std::string> DataGenerator::generateBenignData(size_t size, size_t length) {
    std::vector<std::string> dataset;
    // Random alphanumeric string generation
    
    std::random_device rd;
    std::mt19937 generator(rd());
    
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() -1);
    
    for(size_t i = 0 ; i< size;i++){
        std::string random_string;
        random_string.reserve(length);
        for (size_t j = 0; j < length; ++j) {
            random_string += CHARACTERS[distribution(generator)];
        }
        dataset.push_back(random_string);
    }
    return dataset;
}

 std::vector<std::string> DataGenerator::generateAdversarialData(size_t numPairs) {
    std::vector<std::string> dataset;
    // TODO: Implement Meet-in-the-Middle combinatorial string generation
    return dataset;
}
