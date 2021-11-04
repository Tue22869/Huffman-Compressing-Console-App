#pragma once

#include <string>
#include <vector>
#include <fstream>

class Reader {
public:
    Reader(std::ifstream& input) : input_(input) {
    }
    int Get();
    bool GetBit();

private:
    unsigned char buffer_ = 0;
    size_t buffer_size_ = 0;
    std::istream& input_;
};
