#include <iostream>
#include <string>
#include <numeric>
#include "Day14.h"
#include "RockRoll.h"


std::vector<std::string> Day14::run(std::ifstream &input) {
    std::vector<std::string> out;
    RockRoll rr(input);
    out.push_back(std::to_string(rr.getRollScore()));
    out.push_back(std::to_string(rr.getRollScore2()));
    return out;
}