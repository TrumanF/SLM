#pragma once

#include "GramFrequency.h"

#include <string>
#include <random>

class TextGenerator {
    public:
        TextGenerator(const GramFrequency& model, int output_k);

        std::string generate();
    private:
        std::string starting_gram();
        char next_char(std::string current_gram);
        const GramFrequency& model;
        const int output_k;
        std::mt19937 gen{std::random_device{}()};
};