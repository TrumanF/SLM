#pragma once

#include "GramFrequency.h"

#include <optional>
#include <random>
#include <string>

class TextGenerator {
    public:
        TextGenerator(const GramFrequency& model, int output_k);
        std::string generate();

    private:
        const GramFrequency& model;
        int output_k;
        std::mt19937 gen{std::random_device{}()};
        std::string starting_gram();
        std::optional<char> next_char(const std::string& current_gram);
};