#include <iostream>
#include <istream>
#include <vector>
#include "Decoder.h"
#include "Encoder.h"

int main(int argc, char** argv) {
    if (argv[1][1] == 'c') {
        std::vector<std::string> file_names;
        for (size_t i = 3; i < argc; ++i) {
            file_names.push_back(argv[i]);
        }
        Encoder encode(argv[2]);
        encode.DoEncode(file_names);
    }
    if (argv[1][1] == 'd') {
        Decoder decode(argv[2]);
        decode.DoDecode();
    }
    if (argv[1][1] == 'h') {
        std::cout << "archiver -c archive_name file1 [file2 ...] - заархивировать файлы fil1, file2, ... и сохранить "
                     "результат в файл archive_name.\n"
                     "archiver -d archive_name - разархивировать файлы из архива archive_name и положить в текущую "
                     "директорию. Имена файлов должны сохраняться при архивации и разархивации.\n"
                     "archiver -h - вывести справку по использованию программы."
                  << std::endl;
    }
    return 0;
}
