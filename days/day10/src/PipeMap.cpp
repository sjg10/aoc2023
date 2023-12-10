#include "PipeMap.h"


PipeMap::PipeMap(std::istream &in) {
    unsigned int row = 0;
    for (std::string x; std::getline(in, x);) {
        for (unsigned int col = 0; col < x.size(); col++) {
            switch (x[col]) {
                case 'L': m_map[{row,col}] = {{row - 1,col}, {row,col + 1}}; break;
                case '7': m_map[{row,col}] = {{row + 1,col}, {row,col - 1}}; break;
                case 'F': m_map[{row,col}] = {{row + 1,col}, {row,col + 1}}; break;
                case 'J': m_map[{row,col}] = {{row - 1,col}, {row,col - 1}}; break;
                case '|': m_map[{row,col}] = {{row + 1,col}, {row - 1,col}}; break;
                case '-': m_map[{row,col}] = {{row,col + 1}, {row,col - 1}}; break;
                case 'S': m_start = {row,col}; break;
                default: break;
            }
        }
        row++;
    }
}

unsigned int PipeMap::getBestDistance() {
    auto next = m_start;
    next.first--;
    if (m_map.contains(next)) {
        return getBestDistance(next);
    }
    else {
        next = m_start;
        next.first++;
        if (m_map.contains(next)) {
            return getBestDistance(next);
        }
        else {
            next = m_start;
            next.second--;
            if (m_map.contains(next)) {
                return getBestDistance(next);
            }
            else {
                next = m_start;
                next.second++;
                if (m_map.contains(next)) {
                    return getBestDistance(next);
                }
                else {
                    throw std::runtime_error("S has no neighbours!");
                }
            }
        }
    }
    return 0;
}

unsigned int PipeMap::getBestDistance(std::pair<unsigned int, unsigned int> start2) {
    std::pair<unsigned int, unsigned int> cur = start2;
    std::pair<unsigned int, unsigned int> last = m_start;
    unsigned int distance = 1;
//    std::cout << cur.first << ","  << cur.second << std::endl;
    while (cur != m_start) {
        for (auto const &l: m_map[cur]) {
            if (l != last) {
                last = cur;
                cur = l;
                distance ++;
//                std::cout << cur.first << ","  << cur.second << std::endl;
                break;
            }
        }
    }
    return distance / 2;
}
