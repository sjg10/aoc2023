#pragma once
#include <iostream>
#include <vector>
#include <set>

using Coord=std::pair<unsigned int, unsigned int>;

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    UNKNOWN
};

class PipeMap {
public:
    PipeMap(std::istream &in);
    std::pair<unsigned int, unsigned int> getBestDistance();
private:
    std::pair<unsigned int, unsigned int> getBestDistance(Coord start2, Direction moved);
    bool floodRegions(std::set<Coord> &region, const std::set<Coord> & path);
    std::vector<std::vector<std::vector<Coord>>> m_map; // stores neighbours of each coord
    std::vector<std::vector<char>> m_map_char; // stores char at a coord
    Coord m_start;
};


