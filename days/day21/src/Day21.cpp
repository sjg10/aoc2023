#include <iostream>
#include <string>
#include <numeric>
#include "Day21.h"
#include "GardenPath.h"


std::vector<std::string> Day21::run(std::ifstream &input) {
    std::vector<std::string> out;
    GardenPath gp(input);
    out.push_back(std::to_string(gp.getReachable(64)));
    return out;
}