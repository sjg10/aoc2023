#include "SkyMap.h"

SkyMap::SkyMap(std::istream &in) {
    std::vector<bool> empty_row;
    std::vector<bool> empty_col;
    unsigned int row = 0;
    for(std::string x; std::getline(in, x); row++) {
        empty_row.push_back(true);
        for(unsigned int col = 0; col <x.size();col++) {
            if(row == 0) { empty_col.push_back(true);}
            if(x[col] == '#') {
                empty_row[row] = false;
                empty_col[col] = false;
                m_galaxies.push_back({row,col});
            }
        }
    }
    m_preceeding_empty_rows = std::vector<unsigned long int>(empty_row.size(), 0);
    for(row = 0; row < empty_row.size(); row++) {
        if(empty_row[row]) {
            for (unsigned int row2 = row; row2 < empty_row.size(); row2++) {
                m_preceeding_empty_rows[row2]++;
            }
        }
    }
    m_preceeding_empty_cols = std::vector<unsigned long int>(empty_col.size(), 0);
    for(unsigned int col = 0; col < empty_row.size(); col++) {
        if(empty_col[col]) {
            for (unsigned int col2 = col; col2 < empty_col.size(); col2++) {
                m_preceeding_empty_cols[col2]++;
            }
        }
    }
}
unsigned long int SkyMap::getShortestSum(unsigned long int stepsize) {
    unsigned long int ret = 0;
    for(auto const &a1 : m_galaxies) {
        for(auto const &a2 : m_galaxies) {
            if(a1 < a2) {
                ret += getDistance(getAdjustedCoord(a1, stepsize), getAdjustedCoord(a2, stepsize));
            }
        }
    }
    return ret;
}


unsigned long int SkyMap::getDistance(Coord a, Coord b) {
    return labs((long int) a.first - (long int) b.first) + labs((long int) a.second - (long int) b.second);
}

Coord SkyMap::getAdjustedCoord(Coord a, unsigned long int stepsize) {
    return {a.first + (m_preceeding_empty_rows[a.first] * (stepsize - 1)), a.second + (m_preceeding_empty_cols[a.second] * (stepsize - 1))};
}
