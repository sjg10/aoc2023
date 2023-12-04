#pragma once
#include "Day.h"
#include <list>

class Day04 : public Day {
    public:
        Day04(const std::string &input_filename) : Day(input_filename) {}
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};