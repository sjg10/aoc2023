#include <iostream>
#include <string>
#include <numeric>
#include "Day09.h"
#include "OASIS.h"


std::vector<std::string> Day09::run(std::ifstream &input) {
    std::vector<std::string> out;
    OASIS oa(input);
    out.push_back(std::to_string(oa.getNextTermSumScore()));
    out.push_back(std::to_string(oa.getPrevTermSumScore()));
    return out;
}