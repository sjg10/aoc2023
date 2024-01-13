#include <iostream>
#include <string>
#include <numeric>
#include "Day25.h"
#include "WiringMachine.h"


std::vector<std::string> Day25::run(std::ifstream &input) {
    std::vector<std::string> out;
    WiringMachine wm(input);
    out.push_back(std::to_string(wm.getScore()));
    return out;
}