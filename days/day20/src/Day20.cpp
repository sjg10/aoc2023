#include <iostream>
#include <string>
#include <numeric>
#include "Day20.h"
#include "PulseGen.h"


std::vector<std::string> Day20::run(std::ifstream &input) {
    std::vector<std::string> out;
    PulseGen pg(input);
    auto ret = pg.run(false);
    out.push_back(std::to_string(ret.first));
    out.push_back(std::to_string(ret.second));
    return out;
}