#include <fstream>
#include "Encoder.h"
#include "Statistics.h"
#include "PrefixTree.h"
#include "Reader.h"
#include "Writer.h"

const size_t FILENAME_END = 256;
const size_t ONE_MORE_FILE = 257;
const size_t ARCHIVE_END = 258;

void Encoder::DoEncode(std::vector<std::string> file_names) {
    std::ofstream output(archive_name_, std::ios::binary | std::ios::out);
    Writer our_output(output);
    for (size_t i = 0; i < file_names.size(); ++i) {
        GetStat statistics_of_file;
        if (i != file_names.size() - 1) {
            statistics_of_file.GetNumbers(file_names[i]);
        } else {
            statistics_of_file.GetNumbers(file_names[i]);
        }

        PrefixTree huffman_code = PrefixTree(statistics_of_file.numbers_of_symbols);

        std::ifstream input;
        input.open(file_names[i], std::ios::binary | std::ios::in);
        Reader our_file(input);

        our_output.DataBlock(huffman_code.symbol_to_code);

        for (size_t j = 0; j < file_names[i].length(); ++j) {
            our_output.Writing(huffman_code.symbol_to_code[file_names[i][j]]);
        }
        our_output.Writing(huffman_code.symbol_to_code[FILENAME_END]);
        while (!input.eof()) {
            size_t symbol = our_file.Get();
            if (!input.eof()) {
                our_output.Writing(huffman_code.symbol_to_code[symbol]);
            }
        }
        if (i != file_names.size() - 1) {
            our_output.Writing(huffman_code.symbol_to_code[ONE_MORE_FILE]);
        } else {
            our_output.Writing(huffman_code.symbol_to_code[ARCHIVE_END]);
        }
    }
}
