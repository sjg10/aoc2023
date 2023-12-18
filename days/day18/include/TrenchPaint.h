#pragma once
#include <map>
#include <vector>
#include <iostream>

using Coord = std::pair<int, int>;

enum Tile {
    LEFT,
    UP,
    RIGHT,
    DOWN,
    NONE
};

class TrenchPaint {
public:
    TrenchPaint(std::istream &in);
    unsigned int getInterior();
private:
    std::map<Coord, std::tuple<Tile, Tile, uint32_t>> m_map;
    std::vector<std::pair<Coord, Tile>> m_path;
    int xmax = 0 ;
    int xmin = 0 ;
    int ymax = 0 ;
    int ymin = 0 ;
};