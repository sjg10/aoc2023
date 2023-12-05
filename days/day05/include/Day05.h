#pragma once
#include "Day.h"
#include <list>

class Day05 : public Day {
    public:
        Day05(const std::string &input_filename) : Day(input_filename) {}
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};