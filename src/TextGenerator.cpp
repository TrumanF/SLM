
#include "TextGenerator.h"

#include <stdexcept>
#include <vector>

TextGenerator::TextGenerator(const GramFrequency& model, int output_k) : model(model), output_k(output_k) {}


std::string TextGenerator::starting_gram() {
    std::vector<std::string> grams;
    std::vector<double> weights;

    for (const auto& [gram, data] : model.get_frequency_map()) {
        grams.push_back(gram);
        weights.push_back(data.frequency);
    }

    if (grams.empty()) {
        return "";
    }
    std::discrete_distribution<int> dist(weights.begin(), weights.end());

    return grams[dist(gen)];
}


std::optional<char> TextGenerator::next_char(const std::string& current_gram) {
    const auto& next_char_map = model.get_next_char_map();

    if (next_char_map.find(current_gram) == next_char_map.end()) { // if gram does not exist in next_char_map
        if (model.get_alpha() == 0.0) {
            return std::nullopt; // with alpha=0, we just end text generation
        }

        const auto& alphabet = model.get_alphabet();
        if (alphabet.empty()) {
            return std::nullopt;
        }

        std::vector<char> chars(alphabet.begin(), alphabet.end());
        std::uniform_int_distribution<int> dist(0, chars.size() - 1);
        
        return chars[dist(gen)];
    }

    std::vector<char> chars;
    std::vector<double> weights;

    for (const auto& [character, data] : next_char_map.at(current_gram)) {
        chars.push_back(character);
        weights.push_back(data.cprobability);
    }

    if (chars.empty()) {
        return std::nullopt;
    }

    std::discrete_distribution<int> dist(weights.begin(), weights.end());
    return chars[dist(gen)];
}


std::string TextGenerator::generate() {
    std::string start_gram = starting_gram();

    std::string output_str = start_gram;

    while (output_str.size() < output_k) {
        const int k = model.get_k();

        std::string current_gram = output_str.substr(output_str.size() - k);
        std::optional<char> next = next_char(current_gram);

        if (!next.has_value()) {
            break;
        }
        output_str += *next;
    }

    return output_str;
}
