#include <iostream>
#include <string>
#include <numeric>
#include "Day08.h"
#include "DesertMap.h"


std::vector<std::string> Day08::run(std::ifstream &input) {
    std::vector<std::string> out;
    DesertMap dm(input);
    out.push_back(std::to_string(dm.navigate()));
    out.push_back(std::to_string(dm.navigateGhosts()));
    return out;
}