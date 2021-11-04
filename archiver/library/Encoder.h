#pragma once

#include <vector>
#include <string>

class Encoder {
public:
    Encoder(std::string archive_name) {
        archive_name_ = archive_name;
    };
    void DoEncode(std::vector<std::string> file_names);

private:
    std::string archive_name_;
};
