#include "GramFrequency.h"
#include <fstream>
#include <deque>
#include <iostream>
#include <stdexcept>

GramFrequency::GramFrequency(int k, std::string filename) {
    init_maps(k, filename);
}

void GramFrequency::init_maps(int k, std::string filename) {
    if (k <= 0) {
        throw std::invalid_argument("k must be a positive integer");
    }

    std::ifstream input(filename);
    if (!input) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::deque<char> window;
    std::size_t total_kgrams = 0;
    char ch;

    while (input.get(ch)) {
        if (window.size() == k) {
            std::string key(window.begin(), window.end());
            frequency_map[key].count++;
            next_char_map[key][ch].count++;
        }

        window.push_back(ch);

        if (window.size() > k) {
            window.pop_front();
        }
    }

    if (window.size() == k) {
        std::string key(window.begin(), window.end());
        frequency_map[key].count++;
    }

    for (const auto& [key, data] : frequency_map) {
        total_kgrams += data.count;
    }

    // Calculate each k-gram's relative frequency.
    if (total_kgrams > 0) {
        for (auto& [key, data] : frequency_map) {
            data.frequency =
                data.count / total_kgrams;
        }
    }
}

void GramFrequency::print_frequency_map() {
    for (const auto& [key, data] : frequency_map) {
        std::cout << key << " | "
                  << data.count << " | "
                  << data.frequency << '\n';
    }
}