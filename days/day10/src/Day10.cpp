#include <iostream>
#include <string>
#include <numeric>
#include "Day10.h"
#include "PipeMap.h"


std::vector<std::string> Day10::run(std::ifstream &input) {
    std::vector<std::string> out;
    PipeMap pm(input);
    out.push_back(std::to_string(pm.getBestDistance()));
    return out;
}