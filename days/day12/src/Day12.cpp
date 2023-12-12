#include <iostream>
#include <string>
#include <numeric>
#include "Day12.h"
#include "SpringMap.h"


std::vector<std::string> Day12::run(std::ifstream &input) {
    std::vector<std::string> out;
    SpringMap sm(input);
    auto ret = sm.getValidOptionsSum();
    out.push_back(std::to_string(ret.first));
    out.push_back(std::to_string(ret.second));
    return out;
}