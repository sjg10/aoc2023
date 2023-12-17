#include <iostream>
#include <string>
#include <numeric>
#include "Day17.h"
#include "CrucibleMap.h"


std::vector<std::string> Day17::run(std::ifstream &input) {
    std::vector<std::string> out;
    CrucibleMap cm(input);
    out.push_back(std::to_string(cm.getShortestPath()));
    return out;
}