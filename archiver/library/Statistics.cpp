#include "Statistics.h"
#include "Reader.h"

const size_t FILENAME_END = 256;
const size_t ONE_MORE_FILE = 257;
const size_t ARCHIVE_END = 258;

void GetStat::GetNumbers(std::string file_name) {
    std::ifstream input;
    input.open(file_name, std::ios::binary | std::ios::in);
    Reader our_file(input);
    for (size_t j = 0; j < file_name.length(); ++j) {
        ++numbers_of_symbols[file_name[j]];
    }
    ++numbers_of_symbols[FILENAME_END];
    while (!input.eof()) {
        size_t symbol = static_cast<size_t>(our_file.Get());
        if (!input.eof()) {
            ++numbers_of_symbols[symbol];
        }
    }
    ++numbers_of_symbols[ONE_MORE_FILE];
    ++numbers_of_symbols[ARCHIVE_END];
}
