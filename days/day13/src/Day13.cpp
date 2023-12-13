#include <iostream>
#include <string>
#include <numeric>
#include "Day13.h"
#include "AshMap.h"


std::vector<std::string> Day13::run(std::ifstream &input) {
    std::vector<std::string> out;
    AshMaps am(input);
    auto ret = am.getReflectiveIndexTotal();
    out.push_back(std::to_string(ret.first));
    out.push_back(std::to_string(ret.second));
    return out;
}