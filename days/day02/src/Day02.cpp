#include <iostream>
#include <string>
#include <numeric>
#include "Day02.h"
#include "CubeGame.h"


std::vector<std::string> Day02::run(std::ifstream &input) {
    std::vector<std::string> out;
    std::string read_line;
    unsigned int sum = 0;
    unsigned int psum = 0;
    for(std::string x; std::getline(input, x);) {
        auto cg = CubeGame(x);
        sum += cg.comptaibleScore(12,13,14);
        psum += cg.powerScore();
    }
    out.push_back(std::to_string(sum));
    out.push_back(std::to_string(psum));
    return out;
}