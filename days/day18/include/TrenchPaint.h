#pragma once
#include <map>
#include <vector>
#include <iostream>

using Coord = std::pair<long int, long int>;

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
    unsigned long int getInterior();
    unsigned long int getInterior2();
private:
    std::vector<Coord> m_corners;
    std::vector<Coord> m_corners2;
    long int m_boundary_size;
    long int m_boundary_size2;
    int xmax = 0 ;
    int xmin = 0 ;
    int ymax = 0 ;
    int ymin = 0 ;
};