#include <iostream>
#include <string>
#include <numeric>
#include <cmath>
#include <regex>
#include "Day06.h"


std::vector<std::string> Day06::run(std::ifstream &input) {
    std::vector<std::string> out;
    std::string read_line;
    std::vector<std::pair<unsigned int, unsigned int>> races = parseScores(input);
    auto ret = getScore(races);
    out.push_back(std::to_string(ret.first));
    out.push_back(std::to_string(ret.second));
    return out;
}

std::vector<std::pair<unsigned int, unsigned int>> Day06::parseScores(std::istream &input){
    std::vector<std::pair<unsigned int, unsigned int>> races;
    std::string read_line;
    getline(input, read_line);
    std::regex num_regex("(\\d+)");
    auto n_begin = 
    std::sregex_iterator(read_line.begin(), read_line.end(), num_regex);
    auto n_end = std::sregex_iterator();
    for (std::sregex_iterator i = n_begin; i != n_end; ++i) {
        races.push_back({std::stoul(i->str()), 0});
    }

    getline(input, read_line);
    n_begin =  std::sregex_iterator(read_line.begin(), read_line.end(), num_regex);
    n_end = std::sregex_iterator();
    unsigned int j = 0;
    for (std::sregex_iterator i = n_begin; i != n_end; ++i,  ++j) {
        races[j].second = std::stoul(i->str());
    }
    return races;
}

std::pair<unsigned long int, unsigned long int> Day06::getScore(std::vector<std::pair<unsigned int, unsigned int>> races) {
    unsigned long int ret1 = 1;
    for (auto const &race:races) {
        ret1 *= getScore(race.first, race.second);
    }
    unsigned long int bigT = 0;
    unsigned long int bigD = 0;
    unsigned long int shiftT = 0;
    unsigned long int shiftD = 0;
    for (auto i = races.rbegin(); i != races.rend(); ++i ) { 
        bigT += ((unsigned long int)(i->first) * pow(10, shiftT));
        shiftT += ceil(log10(i->first)) ;
        bigD += ((unsigned long int)(i->second) * pow(10, shiftD));
        shiftD += ceil(log10(i->second));
    }
    return {ret1, getScore(bigT,bigD)};
}

unsigned long int Day06::getScore(unsigned long int T, unsigned long int D) {
        double det = sqrt((T*T) - (4*D));
        unsigned long int min = ceil((T - det) / 2);
        unsigned long int max = floor((T + det) / 2);
        // Delete boundaries
        if ((min * min) - (T * min) + D == 0) {min++;}
        if ((max * max) - (T * max) + D == 0) {max--;}
        return ((max - min) + 1);

}
