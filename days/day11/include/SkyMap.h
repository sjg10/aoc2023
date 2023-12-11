#pragma once
#include <iostream>
#include <vector>

using Coord = std::pair<unsigned long int, unsigned long int>;

class SkyMap {
public:
    SkyMap(std::istream &in);
    unsigned long int getShortestSum(unsigned long int stepsize = 2);
private:
    static unsigned long int getDistance(Coord a, Coord b);
    Coord getAdjustedCoord(Coord a, unsigned long int stepsize);
    std::vector<Coord> m_galaxies;
    std::vector<unsigned long int> m_preceeding_empty_rows;
    std::vector<unsigned long int> m_preceeding_empty_cols;
};

