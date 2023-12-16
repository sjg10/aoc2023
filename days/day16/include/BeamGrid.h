#pragma once
#include <iostream>
#include <vector>

enum Direction {
    NORTH = 0,
    SOUTH = 1,
    EAST = 2,
    WEST = 3
};

using Coord = std::pair<unsigned int, unsigned int>;

using State = std::pair<Coord, Direction>;

class BeamGrid {
public:
    BeamGrid(std::istream &in);
    unsigned int walk();
    unsigned int walk2();
private:
    unsigned int walk(State start);
    std::vector<std::vector<char>> m_map;
};
