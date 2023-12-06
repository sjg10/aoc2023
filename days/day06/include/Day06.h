#pragma once
#include "Day.h"
#include <list>

class Day06 : public Day {
    public:
        Day06(const std::string &input_filename) : Day(input_filename) {}
        static std::vector<std::pair<unsigned int, unsigned int>> parseScores(std::istream & input);
        static std::pair<unsigned long int, unsigned long int> getScore(std::vector<std::pair<unsigned int, unsigned int>> races);
    private:
        static unsigned long int getScore(unsigned long int T, unsigned long int D);
        std::vector<std::string> run(std::ifstream &input) override;
};