#include <iostream>
#include <string>
#include <numeric>
#include "Day05.h"
#include "SoilAlmanac.h"


std::vector<std::string> Day05::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto sa = SoilAlmanac(input);
    out.push_back(std::to_string(sa.getLowestSeedLocation()));
    out.push_back(std::to_string(sa.getLowestSeedLocationRanges()));
    return out;
}