#pragma once
#include <iostream>
#include <map>
#include <vector>

class PipeMap {
public:
    PipeMap(std::istream &in);
    unsigned int getBestDistance();
private:
    unsigned int getBestDistance(std::pair<unsigned int, unsigned int> start2);
    std::map<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>> m_map;
    std::pair<unsigned int, unsigned int> m_start;
};


