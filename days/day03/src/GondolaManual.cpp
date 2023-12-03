#include "GondolaManual.h"
#include <cmath>

GondolaManual::GondolaManual(std::istream &input) {
    unsigned int row = 0;
    bool in_number=false;
    for(std::string x; std::getline(input, x);) {
        m_map.push_back(std::vector<char>());
        for (unsigned int col=0; col < x.size(); col++) {
            if (x[col] >= '0' && x[col] <= '9') {
                if (!in_number) {
                    m_value_locations.push_back({row,col});
                    m_values.push_back(x[col] - '0');
                    in_number = true;
                }
                else {
                    m_values.back() *= 10; 
                    m_values.back() += (x[col] - '0'); 
                }
                m_map.back().push_back('.');
            }
            else {
                in_number = false;
                m_map.back().push_back(x[col]);
                if(x[col] == '*') {
                    m_star_neighbours[{row,col}] = std::set<unsigned int>();
                }
            }
        }
        row += 1;
    }
    for (unsigned int i = 0; i < m_values.size(); i++) {
        parseNumberNeighbours(i);
    }
}

bool GondolaManual::checkLocation(unsigned int i, unsigned int r, unsigned int c) {
    if (m_map[r][c] != '.') {
        if (m_map[r][c] == '*') {m_star_neighbours[{r, c}].insert(i);}
        return true;
    }
    return false;
}
void GondolaManual::parseNumberNeighbours(unsigned int i) {
    bool ispart = false;
    std::pair<unsigned int, unsigned int> loc = m_value_locations[i];
    unsigned int value_length = int(log10(m_values[i]) + 1);
    unsigned int l_check = (loc.second >= 1) ? loc.second - 1 : 0;
    unsigned int r_check = ((loc.second + value_length) < m_map[0].size()) ? (loc.second + value_length) : (loc.second + value_length) - 1;
    // Check above
    if (loc.first > 0) {
        for(unsigned int j = l_check; j <= r_check; j++) {
            ispart |= checkLocation(i, loc.first - 1, j);
        }
    }
    // check same row. Dont worry if on edge as then l/rcheck will check within the digit
    // which is '.' so will be ignored.
    ispart |= checkLocation(i, loc.first, l_check);
    ispart |= checkLocation(i, loc.first, r_check);
    //check below
    if (loc.first < m_map.size() - 1) {
        for(unsigned int j = l_check; j <= r_check; j++) {
            ispart |= checkLocation(i, loc.first + 1, j);
        }
    }
    if (ispart) m_part_offsets.push_back(i);
}


unsigned int GondolaManual::getPartScore(){
    unsigned int sum = 0;
    for (auto const &i: m_part_offsets) {
        sum += m_values[i];
    }
    return sum;
}
unsigned int GondolaManual::getGearScore(){
    unsigned int sum = 0;
    for (auto const& [loc, neighbours] : m_star_neighbours) {
        if (neighbours.size() == 2) {
            sum += m_values[*neighbours.begin()] * m_values[*(neighbours.rbegin())];
        }
    }
    return sum;
}
