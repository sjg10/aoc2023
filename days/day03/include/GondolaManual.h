#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

class GondolaManual {
public:
    GondolaManual(std::istream &input);
    unsigned int getPartScore();
    unsigned int getGearScore();
private:
    /** Build up the map of neighbours of value offset i, check if it is a part */
    void parseNumberNeighbours(unsigned int i);
    /** Return if coord r,c contains a symbol, and mark i as a star neighbour if it is a star */
    bool checkLocation(unsigned int i, unsigned int r, unsigned int c);
    /* Store all chars replacing digits with '.' */
    std::vector<std::vector<char>> m_map;

    /* List of locations of start digit of numbers in map */
    std::vector<std::pair<unsigned int, unsigned int>> m_value_locations;
    /* List of values of numbers in map, idx's to match m_value_locations */
    std::vector<unsigned int> m_values;
    /* List of the values above that are engine parts */
    std::vector<unsigned int> m_part_offsets;

    /* Map of locations of '*' chars in m_map to idxs of values */
    std::map<std::pair<unsigned int, unsigned int>, std::set<unsigned int>> m_star_neighbours;

};