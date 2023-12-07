#include <iostream>
#include <string>
#include <numeric>
#include "Day07.h"
#include "CamelCards.h"


std::vector<std::string> Day07::run(std::ifstream &input) {
    std::vector<std::string> out;
    CamelCards cc(input);
    out.push_back(std::to_string(cc.getScore()));
    out.push_back(std::to_string(cc.getScoreJ()));
    return out;
}