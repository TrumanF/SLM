#include <string>
#include <stdexcept>
#include <iostream>

#include "GramFrequency.h"
#include "TextGenerator.h"

int main(int argc, char* argv[]) {
    if (argc != 4 && argc != 6) { // ensure we have all input arguments required
        throw std::invalid_argument(
            "Usage: ./slm [[-a] alpha] <word_size> <filename> <output_characters>"
        );
    }
    int argv_read_offset;
    double alpha = 0.0;
    if (std::string(argv[1]) == "-a") {
        argv_read_offset = 2;
        alpha = std::stoi(argv[2]);
        if (alpha < 0) {
            throw std::invalid_argument("alpha must be non-negative");
        }
    } else {
        argv_read_offset = 0;
    }

    int k = std::stoi(argv[1 + argv_read_offset]);
    std::string filename = argv[2 + argv_read_offset];
    int output_k = std::stoi(argv[3 + argv_read_offset]);

    GramFrequency newGram(k, filename, alpha);
    TextGenerator generator(newGram, output_k);
    std::cout << generator.generate() << std::endl;

}