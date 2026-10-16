#pragma once

#include <string>
#include <map>
#include <set>

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
        GramFrequency(int k, std::string filename, double alpha = 0.0);   
        
        // getters for TextGenerator to use
        const std::map<std::string, FrequencyData>& get_frequency_map() const;
        const std::map<std::string, std::map<char, ProbabilityData>>& get_next_char_map() const;
        const std::set<char>& get_alphabet() const;
        int get_k() const;
        double get_alpha() const;

        // debug print functions
        void print_frequency_map();
        void print_conditional_probability_map();
    private:
        void init_maps(int k, std::string filename);
        void calculate_probabilities(double alpha); 
        std::map<std::string, FrequencyData> frequency_map;
        std::map<std::string, std::map<char, ProbabilityData>> next_char_map;
        std::set<char> alphabet;
        int k;
        double alpha;

};
