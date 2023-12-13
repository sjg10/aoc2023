#include "AshMap.h"
#include <numeric>

AshMap::AshMap(std::istream &in) {
    unsigned int row = 0;
    for (std::string x; std::getline(in, x);) {
        if (x.size() == 0) break;
        m_rows.push_back(0);
        for (unsigned int col = 0; col < x.size(); col++) {
            if (row == 0) {
                m_cols.push_back(0);
            }
            if (x[col] == '#') {
                m_rows[row] += (1 << col);
                m_cols[col] += (1 << row);
            }
        }
        row++;
    }

}

std::pair<unsigned int, unsigned int> AshMap::getReflectiveIndex() const {
    unsigned int ret = 0;
    unsigned int ret_smudge = 0;
    for ( unsigned int i = 0; i < m_cols.size() - 1; i++) {
        bool found_reflection = true;
        bool found_smudge_reflection = true;
        bool smudged = false;
        for ( unsigned int j = 0; j <= std::min(i, (unsigned int)m_cols.size() - (2 + i)); j++) {
            unsigned int xord = m_cols[i + j + 1] ^ m_cols[i - j];
            unsigned int pc = std::popcount(xord);
            if (pc > 1) {
                found_reflection = false;
                found_smudge_reflection = false;
                break;
            }
            else if(pc == 1 && smudged) {
                found_reflection = false;
                found_smudge_reflection = false;
                break;
            }
            else if (pc == 1 && !smudged) {
                found_reflection = false;
                smudged = true;
            }
        }

        if (found_reflection) {
            ret += i + 1;
        }
        if (found_smudge_reflection & smudged) {
            ret_smudge += i + 1;
        }
    }

    for ( unsigned int i = 0; i < m_rows.size() - 1; i++) {
        bool found_reflection = true;
        bool found_smudge_reflection = true;
        bool smudged = false;
        for ( unsigned int j = 0; j <= std::min(i, (unsigned int)m_rows.size() - (2 + i)); j++) {
            unsigned int xord = (m_rows[i + j + 1] ^ m_rows[i - j]);
            unsigned int pc = std::popcount(xord);
            if (pc > 1) {
                found_reflection = false;
                found_smudge_reflection = false;
                break;
            }
            else if(pc == 1 && smudged) {
                found_reflection = false;
                found_smudge_reflection = false;
                break;
            }
            else if (pc == 1 && !smudged) {
                smudged = true;
                found_reflection = false;
                found_smudge_reflection = true;
            }
        }
        if (found_reflection) {
            ret += 100 * (i + 1);
        }
        if (found_smudge_reflection & smudged) {
            ret_smudge += 100 * (i + 1);
        }
    }
    return {ret, ret_smudge};
}

AshMaps::AshMaps(std::istream &in) {
    while(!in.eof()) {
        m_maps.push_back(AshMap(in));
    }
}

std::pair<unsigned int, unsigned int> AshMaps::getReflectiveIndexTotal() {
    unsigned int ret1 = 0;
    unsigned int ret2 = 0;
    for(auto const &am : m_maps) {
        auto ret = am.getReflectiveIndex();
        ret1 += ret.first;
        ret2 += ret.second;
    }
    return {ret1, ret2};
}