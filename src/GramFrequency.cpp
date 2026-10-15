#include "GramFrequency.h"
#include <fstream>
#include <deque>
#include <iostream>
#include <stdexcept>

GramFrequency::GramFrequency(int k, std::string filename, double alpha) {
    init_maps(k, filename);
    calculate_probabilities(alpha);
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
        alphabet.insert(ch); // add characters to set for later pseudocount calculations
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

    for (const auto& [key, data] : frequency_map) { // getting total_kgrams count
        total_kgrams += data.count;
    }
    if (total_kgrams > 0) { // ensure that we didn't have an empty text
        for (auto& [key, data] : frequency_map) { // calculate total kgram frequency
            data.frequency =
                static_cast<double>(data.count) / total_kgrams;
        }
    }
}

void GramFrequency::calculate_probabilities(double alpha) {
    if (alpha) {
        for (auto& [gram, _] : frequency_map) { // insert every char in alphabet into each grams map
            for (char ch : alphabet) {
                next_char_map[gram][ch];
            }
        }
        for (auto& [gram, next_chars] : next_char_map) {
            int total_transitions = 0;
            for (auto& [ch, data] : next_chars) { // count total characters that follow kgram
                total_transitions += data.count;
            }
            for (auto& [ch, data] : next_chars) {
                data.cprobability =
                    (static_cast<double>(data.count) + alpha) /
                    (total_transitions + alpha * alphabet.size());
            }
        }
    } else { // calculate frequencies without alpha
        for (auto& [gram, next_chars] : next_char_map) {
            int total_transitions = 0;
            for (auto& [ch, data] : next_chars) { // count total characters that follow kgram
                total_transitions += data.count;
            }
            if (total_transitions == 0) {
                continue;
            }
            for (auto& [ch, data] : next_chars) {
                data.cprobability =
                    static_cast<double>(data.count) / total_transitions;
            }
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

void GramFrequency::print_conditional_probability_map() {
    for (const auto& [gram, next_chars] : next_char_map) {
        std::cout << "Gram: \"" << gram << "\"\n";

        for (const auto& [ch, data] : next_chars) {
            std::cout << "  Next character: '";

            if (ch == ' ') {
                std::cout << "[space]";
            } else if (ch == '\n') {
                std::cout << "[newline]";
            } else if (ch == '\t') {
                std::cout << "[tab]";
            } else {
                std::cout << ch;
            }

            std::cout << "' | Count: " << data.count
                      << " | Probability: " << data.cprobability
                      << '\n';
        }

        std::cout << '\n';
    }
}