#pragma once
#include <vector>
#include <array>
#include <string>
#include <iostream>

using Coord = std::pair<unsigned int, unsigned int>;

class GardenPath {
public:
    GardenPath(std::istream &in);
    unsigned int getReachable(unsigned int path_length);
private:
    void dijkstra();
    unsigned int neighbours(const Coord &c, std::array<Coord, 4> &nbors) const;
    std::vector<std::vector<unsigned int>> m_distances;
    Coord m_start;
    std::vector<std::vector<bool>> m_garden;
    unsigned int m_rmax;
    unsigned int m_cmax;
};

