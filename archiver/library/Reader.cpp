#include "Reader.h"

const size_t BUFFER_SIZE = 8;

int Reader::Get() {
    char symbol;
    Reader::input_.read(&symbol, 1);
    return static_cast<size_t>(symbol);
}

bool Reader::GetBit() {
    if (buffer_size_ == BUFFER_SIZE) {
        buffer_size_ = 0;
    }
    if (buffer_size_ == 0) {
        input_.read(reinterpret_cast<char*>(&buffer_), 1);
    }
    bool bit;
    if constexpr (std::endian::native != std::endian::big) {
        bit = ((buffer_ >> buffer_size_) & 1);
    } else {
        bit = ((buffer_ >> (BUFFER_SIZE - 1 - buffer_size_)) & 1);
    }
    ++buffer_size_;
    return bit;
}
