#include "Decoder.h"
#include "Writer.h"

#include <iostream>

const size_t FILENAME_END = 256;
const size_t ONE_MORE_FILE = 257;
const size_t ARCHIVE_END = 258;
const size_t NINE_BIT = 9;

size_t Decoder::GetSymbol(Reader &our_file) {
    bool bit = our_file.GetBit();
    std::vector<bool> ind;
    ind.push_back(bit);
    while (code_to_symbol_.find(ind) == code_to_symbol_.end()) {
        bit = our_file.GetBit();
        ind.push_back(bit);
    }
    return code_to_symbol_[ind];
}

std::string Decoder::GetFileName(Reader &our_file) {
    std::string file_name;
    while (true) {
        size_t symbol = GetSymbol(our_file);
        if (symbol == FILENAME_END) {
            break;
        }
        file_name += static_cast<char>(symbol);
    }
    return file_name;
}

bool Decoder::DecodeOneFile(Reader &our_file) {
    std::vector<int> pow_of_two;
    pow_of_two.push_back(1);
    for (size_t i = 1; i < NINE_BIT; ++i) {
        pow_of_two.push_back(pow_of_two.back() * 2);
    }

    size_t symbols_count = 0;
    for (size_t i = 0; i < NINE_BIT; ++i) {
        bool bit = our_file.GetBit();
        if (bit) {
            symbols_count += static_cast<size_t>(pow_of_two[i]);
        }
    }

    std::vector<std::pair<size_t, size_t>> symbol_to_code;
    for (size_t i = 0; i < symbols_count; ++i) {
        size_t symbol = 0;
        for (size_t j = 0; j < NINE_BIT; ++j) {
            bool bit = our_file.GetBit();
            if (bit) {
                symbol += static_cast<size_t>(pow_of_two[j]);
            }
        }
        symbol_to_code.push_back(std::make_pair(symbol, 0));
    }

    size_t current_index = 0;
    size_t length = 0;
    while (current_index < symbols_count) {
        ++length;
        size_t amount = 0;
        for (size_t j = 0; j < NINE_BIT; ++j) {
            bool e = our_file.GetBit();
            if (e) {
                amount += static_cast<size_t>(pow_of_two[j]);
            }
        }
        for (size_t j = 0; j < amount; ++j) {
            symbol_to_code[current_index].second = length;
            ++current_index;
        }
    }

    std::vector<bool> code;
    size_t previous_size = 0;
    for (size_t i = 0; i < symbols_count; ++i) {
        while (symbol_to_code[i].second > previous_size) {
            ++previous_size;
            code.push_back(0);
        }
        code_to_symbol_[code] = symbol_to_code[i].first;
        size_t j = code.size();
        while (j > 0 && code[j - 1] == 1) {
            code[j - 1] = 0;
            --j;
        }
        if (j == 0) {
            j = 1;
            code.push_back(0);
        }
        code[j - 1] = 1;
    }

    std::string file_name = GetFileName(our_file);

    std::ofstream output(file_name, std::ios::binary | std::ios::out);

    Writer write(output);

    size_t now_symbol;
    while (true) {
        now_symbol = GetSymbol(our_file);
        if (now_symbol == ONE_MORE_FILE || now_symbol == ARCHIVE_END) {
            break;
        }
        write.WritingSymbol(now_symbol);
    }

    if (now_symbol == ONE_MORE_FILE) {
        return false;
    } else {
        return true;
    }
}

void Decoder::DoDecode() {
    std::ifstream input;
    input.open(archive_name_, std::ios::binary | std::ios::in);
    Reader our_file(input);

    while (!DecodeOneFile(our_file)) {
        code_to_symbol_.clear();
    }
}