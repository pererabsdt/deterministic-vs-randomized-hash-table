#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <vector>
#include <string>

const std::string CHARACTERS ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
const std::size_t CHARACTERS_SIZE = CHARACTERS.size();

class DataGenerator {
public:
    // Generates a dataset of random alphanumeric strings
    static void generateBenignData(size_t size, size_t length);
    
    // Generates an adversarial dataset mathematically crafted to collide on V1
    // Number of elements generated will be 2^pairs.
    // e.g. 16 pairs = 65536 strings.
    static std::vector<std::string> generateAdversarialData(size_t numPairs);

    static std::vector<std::string> generateAvalancheData(size_t size, std::string seed);
};

#endif // DATA_GENERATOR_H
