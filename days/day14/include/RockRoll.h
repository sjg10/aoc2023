#pragma once
#include <iostream>
#include <vector>

enum Tile {
    EMPTY,
    CUBE,
    ROUND
};

class RockRoll {
public:
    RockRoll(std::istream &in);
    unsigned int getRollScore();
    unsigned int getRollScore2();
private:
    std::vector<std::vector<Tile>> m_rocks;
};
