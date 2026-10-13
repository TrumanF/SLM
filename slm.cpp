#include <string>
#include <stdexcept>

int main(int argc, char* argv[]) {
    if (argc != 4 || argc != 6) { // ensure we have all input arguments required
        throw std::invalid_argument(
            "Usage: ./slm [[-a] pseudocount] <word_size> <filename> <output_characters>"
        );
    }
    int argv_read_offset;
    int pseudocount;
    if (std::string(argv[1]) == "-a") {
        argv_read_offset = 2;
        pseudocount = std::stoi(argv[2]);
    } else {
        argv_read_offset = 0;
    }

    int k = std::stoi(argv[1 + argv_read_offset]);
    std::string filename = argv[2 + argv_read_offset];
    int output_k = std::stoi(argv[3 + argv_read_offset]);

}