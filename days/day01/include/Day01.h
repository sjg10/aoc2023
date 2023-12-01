#pragma once
#include "Day.h"
#include <list>

class Day01 : public Day {
    public:
        Day01(const std::string &input_filename) : Day(input_filename) {}
        static std::pair<unsigned int, unsigned int> getCalibrationSum(std::istream &input);
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};