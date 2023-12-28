#include <iostream>
#include <string>
#include <numeric>
#include "Day22.h"
#include "BlockFall.h"


std::vector<std::string> Day22::run(std::ifstream &input) {
    std::vector<std::string> out;
    BlockField bf(input);

    auto ret = bf.getRemovable();
    out.push_back(std::to_string(ret.first));
    out.push_back(std::to_string(ret.second));
    return out;
}