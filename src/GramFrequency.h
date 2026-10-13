#include <string>
#include <map>

class GramFrequency {
    public:
        GramFrequency(int k, std::string filename);
    private:
        std::map<std::string, float> frequency_map;
};