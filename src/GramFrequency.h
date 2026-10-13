#pragma once

#include <string>
#include <map>

struct FrequencyData {
    int count = 0;
    double frequency = 0.0;
};
struct ProbabilityData {
    int count = 0;
    double cprobability = 0.0;
};

class GramFrequency {
    public:
        GramFrequency(int k, std::string filename);        
        void print_frequency_map();
    private:
        void init_maps(int k, std::string filename);
        std::map<std::string, FrequencyData> frequency_map;
        std::map<std::string, std::map<char, ProbabilityData>> next_char_map;

};
