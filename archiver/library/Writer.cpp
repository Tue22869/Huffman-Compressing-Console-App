#include <Encoder.h>
#include <Writer.h>

const size_t BUFFER_SIZE = 8;

Writer::~Writer() {
    if (buffer_size_ > 0) {
        output_.write(reinterpret_cast<const char *>(&buffer_), buffer_size_);
        buffer_size_ = 0;
        buffer_ = 0;
    }
}

std::vector<bool> Writer::ReformateNumber(size_t number, size_t length) {
    uint16_t number_bit = static_cast<uint16_t>(number);
    const uint16_t mask = 0b1'1111'1111;
    number_bit &= mask;
    std::vector<bool> reformated_number;
    for (size_t i = 0; i < length; ++i) {
        reformated_number.push_back(number_bit % 2);
        number_bit /= 2;
    }
    return reformated_number;
}

void Writer::Writing(std::vector<bool> const &write_num) {
    for (size_t i = 0; i < write_num.size(); ++i) {
        if constexpr (std::endian::native != std::endian::big) {
            buffer_ += (static_cast<uint8_t>(write_num[i]) << buffer_size_);
        } else {
            buffer_ += (static_cast<uint8_t>(write_num[i]) << (BUFFER_SIZE - 1 - buffer_size_));
        }
        ++buffer_size_;
        if (buffer_size_ == BUFFER_SIZE) {
            output_.write(reinterpret_cast<const char *>(&buffer_), 1);
            buffer_size_ = 0;
            buffer_ = 0;
        }
    }
}

void Writer::WritingSymbol(size_t const &symbol) {
    output_.write(reinterpret_cast<const char *>(&symbol), 1);
}

void Writer::DataBlock(std::map<size_t, std::vector<bool>> &symbol_to_code) {
    size_t symbols_count = 0;
    for (auto i : symbol_to_code) {
        ++symbols_count;
        huffman_symbols_.insert(std::make_pair(i.second.size(), i.first));
    }

    const size_t max_symbol_code_size = huffman_symbols_.rbegin()->first;
    std::vector<size_t> each_length;
    each_length.assign(max_symbol_code_size, 0);

    Writing(ReformateNumber(symbols_count, 9));
    while (!huffman_symbols_.empty()) {
        Writing(ReformateNumber(huffman_symbols_.begin()->second, 9));
        ++each_length[huffman_symbols_.begin()->first - 1];
        huffman_symbols_.erase(huffman_symbols_.begin());
    }

    for (size_t i = 0; i < max_symbol_code_size; ++i) {
        Writing(ReformateNumber(each_length[i], 9));
    }
}