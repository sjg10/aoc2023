#include <iostream>
#include <string>
#include <numeric>
#include "Day23.h"
#include "ForestWalk.h"


std::vector<std::string> Day23::run(std::ifstream &input) {
    std::vector<std::string> out;
    ForestWalk fw(input);
    out.push_back(std::to_string(fw.getLongestPath()));
    out.push_back(std::to_string(fw.getLongestPath(false)));
    return out;
}