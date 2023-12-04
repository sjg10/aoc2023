#include <iostream>
#include <string>
#include <numeric>
#include "Day04.h"
#include "Scratchcards.h"


std::vector<std::string> Day04::run(std::ifstream &input) {
    std::vector<std::string> out;
    auto sc = Scratchcards(input);
    auto ret = sc.getTotalScores();
    out.push_back(std::to_string(ret.first));
    out.push_back(std::to_string(ret.second));
    return out;
}