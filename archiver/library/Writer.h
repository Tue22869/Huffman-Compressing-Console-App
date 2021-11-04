#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>

size_t CountBits(size_t number);

class Writer {
public:
    Writer(std::ofstream &output) : output_(output) {
    }
    ~Writer();
    void Writing(std::vector<bool> const &write_num);
    void DataBlock(std::map<size_t, std::vector<bool>> &symbol_to_code);
    std::vector<bool> ReformateNumber(size_t number, size_t length);
    void WritingSymbol(size_t const &symbol);

private:
    std::ofstream &output_;
    unsigned char buffer_ = 0;
    size_t buffer_size_ = 0;

    std::set<std::pair<size_t, size_t>> huffman_symbols_;
};
