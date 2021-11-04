#pragma once

#include <vector>
#include <string>

class GetStat {
public:
    GetStat() {
        numbers_of_symbols.assign(260, 0);
    }
    std::vector<size_t> numbers_of_symbols;
    void GetNumbers(std::string file_name);

private:
};
