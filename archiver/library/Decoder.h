#pragma once

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Reader.h"

class Decoder {
public:
    Decoder(std::string archive_name) {
        archive_name_ = archive_name;
    }

    void DoDecode();

private:
    std::string archive_name_;

    bool DecodeOneFile(Reader &our_file);
    std::string GetFileName(Reader &our_file);
    size_t GetSymbol(Reader &our_file);

    std::map<std::vector<bool>, size_t> code_to_symbol_;
};
