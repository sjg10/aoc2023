#include <iostream>
#include <string>
#include <numeric>
#include "Day11.h"
#include "SkyMap.h"


std::vector<std::string> Day11::run(std::ifstream &input) {
    std::vector<std::string> out;
    SkyMap sm(input);
    out.push_back(std::to_string(sm.getShortestSum()));
    out.push_back(std::to_string(sm.getShortestSum(1000000)));
    return out;
}