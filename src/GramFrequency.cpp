#include "GramFrequency.h"
#include <fstream>
#include <deque>
#include <iostream>

GramFrequency::GramFrequency(int k, std::string filename) {
    init_kgram_vector(k, filename); // modifies kgram_vector inplace with input file data
    print_frequency_map();
};

void GramFrequency::init_kgram_vector(int k, std::string filename) {
    std::ifstream input(filename);
    if (!input) {
        throw std::runtime_error("Error opening file");
    }

    // if (total_words == 0) {
    //     throw std::length_error("Input text has no words");
    // }

    std::deque<char> window;
    int total_windows = 0;
    char ch;
    while (input.get(ch)) {
        window.push_back(ch);

        if (window.size() > k) { // if the deque reaches k+1 characters, pop the top one so the window stays at k
            window.pop_front();
        }
        if (window.size() == k) { // once deque reaches k, cast to string, store in frequency map
            std::string key(window.begin(), window.end());
            frequency_map[key].count++;
            total_windows++;
        }
    }
    for (auto& [key, data] : frequency_map) {
        data.frequency =
            100.0 * data.count / total_windows;
    }
}

void GramFrequency::print_frequency_map() {
    for (const auto& [key, data] : frequency_map) {
        std::cout << key << " | "
                  << data.count << " | "
                  << data.frequency << "%\n";
    }
}