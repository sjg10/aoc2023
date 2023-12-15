#pragma once
#include "Day.h"
#include <list>

class Day15 : public Day {
    public:
        Day15(const std::string &input_filename) : Day(input_filename) {}
        static unsigned int HASH(const std::string &x);
        static unsigned int HASH2(const std::string &x);
    private:
        std::vector<std::string> run(std::ifstream &input) override;
};