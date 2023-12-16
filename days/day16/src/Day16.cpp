#include <iostream>
#include <string>
#include <numeric>
#include "Day16.h"
#include "BeamGrid.h"


std::vector<std::string> Day16::run(std::ifstream &input) {
    std::vector<std::string> out;
    BeamGrid bm(input);
    out.push_back(std::to_string(bm.walk()));
    out.push_back(std::to_string(bm.walk2()));
    return out;
}