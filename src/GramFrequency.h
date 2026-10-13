#pragma once

#include <string>
#include <map>
#include <vector>

struct WordData {
    int count = 0;
    double frequency = 0.0;
};

class GramFrequency {
    public:
        GramFrequency(int k, std::string filename);


        void init_kgram_vector(int k, std::string filename);
        // void update_frequency_map(std::string word);
        void print_frequency_map();

    private:
        std::map<std::string, WordData> frequency_map;
        std::vector<std::string> kgram_vector;

};
