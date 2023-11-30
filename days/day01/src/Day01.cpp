#include <iostream>
#include <string>
#include <numeric>
#include "Day01.h"


std::vector<std::string> Day01::run(std::ifstream &input) {
    std::vector<std::string> out;
    std::string read_line;
    getline(input, read_line);
    out.push_back("hello world");
    out.push_back(read_line);
    return out;
}