#include <iostream>
#include <string>
#include <numeric>
#include "Day18.h"
#include "TrenchPaint.h"


std::vector<std::string> Day18::run(std::ifstream &input) {
    std::vector<std::string> out;
    std::string read_line;
    TrenchPaint tp(input);
    out.push_back(std::to_string(tp.getInterior()));
    return out;
}