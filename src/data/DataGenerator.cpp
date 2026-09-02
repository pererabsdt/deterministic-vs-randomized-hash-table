#include "data/DataGenerator.h"
#include <random>
#include <string>
using namespace std;

vector<string> DataGenerator::generateBenignData(size_t size, size_t length) {
    vector<string> dataset;
    // Random alphanumeric string generation
    
    random_device rd;
    mt19937 generator(rd());
    
    uniform_int_distribution<> distribution(0, CHARACTERS.size() -1);
    
    for(size_t i = 0 ; i< size;i++){
        string random_string;
        random_string.reserve(length);
        for (size_t j = 0; j < length; ++j) {
            random_string += CHARACTERS[distribution(generator)];
        }
        dataset.push_back(random_string);
    }
    return dataset;
}

vector<string> DataGenerator::generateAdversarialData(size_t numPairs) {
    vector<string> dataset;
    // TODO: Implement Meet-in-the-Middle combinatorial string generation
    return dataset;
}
