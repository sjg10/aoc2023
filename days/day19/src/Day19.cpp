#include <iostream>
#include <string>
#include <numeric>
#include "Day19.h"
#include "MachineSort.h"


std::vector<std::string> Day19::run(std::ifstream &input) {
    std::vector<std::string> out;
    MachineSort ms(input);
    out.push_back(std::to_string(ms.sort()));
    return out;
}