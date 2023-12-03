#include <iostream>
#include <string>
#include <numeric>
#include "Day03.h"
#include "GondolaManual.h"


std::vector<std::string> Day03::run(std::ifstream &input) {
    std::vector<std::string> out;

    auto gm = GondolaManual(input);
    out.push_back(std::to_string(gm.getPartScore()));
    out.push_back(std::to_string(gm.getGearScore()));
    return out;
}