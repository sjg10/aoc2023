#include <iostream>
#include <string>
#include <numeric>
#include "Day24.h"
#include "HailStorm.h"


std::vector<std::string> Day24::run(std::ifstream &input) {
    std::vector<std::string> out;
    HailStorm hs(input);
    out.push_back(std::to_string(hs.getCollisions(200000000000000, 400000000000000)));
    return out;
}