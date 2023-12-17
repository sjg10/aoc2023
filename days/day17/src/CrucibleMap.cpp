#include "CrucibleMap.h"
#include <list>
#include <limits>
#include <array>
#include <set>

std::ostream& operator<<(std::ostream& os, const Pos &pm) {
    os << "(" << pm.r << "," << pm.c << ",";
    switch (pm.d) {
        case INVALID: os << "I"; break;
        case NORTH: os << "N"; break;
        case SOUTH: os << "S"; break;
        case EAST: os << "E"; break;
        case WEST: os << "W"; break;
        default: os << "?"; break;
    }
    os << ",";
    switch (pm.d1) {
        case INVALID: os << "I"; break;
        case NORTH: os << "N"; break;
        case SOUTH: os << "S"; break;
        case EAST: os << "E"; break;
        case WEST: os << "W"; break;
        default: os << "?"; break;
    }
    os << ",";
    switch (pm.d2) {
        case INVALID: os << "I"; break;
        case NORTH: os << "N"; break;
        case SOUTH: os << "S"; break;
        case EAST: os << "E"; break;
        case WEST: os << "W"; break;
        default: os << "?"; break;
    }
    os << ")";
    return os;
}

template <class T>
PosMap<T>::PosMap(unsigned int rmax, unsigned int cmax) : rmax(rmax), cmax(cmax) {
    m_container = std::vector<T>((rmax + 1) * (cmax + 1) * 5 * 5 * 5);
}

PosMapBool::PosMapBool(unsigned int rmax, unsigned int cmax) : rmax(rmax), cmax(cmax) {
    m_container = std::vector<bool>((rmax + 1) * (cmax + 1) * 5 * 5 * 5);
}

std::vector<bool>::reference PosMapBool::operator[](const Pos &p) {
    return m_container[
            (p.r * (5 * 5 * 5 * (cmax + 1))) +
            (p.c * 5 * 5 * 5) +
            (p.d * 5 * 5) +
            (p.d1 * 5) +
            (p.d2)
    ];
}

template <class T>
T& PosMap<T>::operator[](const Pos &p) {
    return m_container[
            (p.r * (5 * 5 * 5 * (cmax + 1))) +
            (p.c * 5 * 5 * 5) +
            (p.d * 5 * 5) +
            (p.d1 * 5) +
            (p.d2)
    ];
}

CrucibleMap::CrucibleMap(std::istream &in){
    for(std::string x; std::getline(in, x);) {
        m_values.push_back(std::vector<unsigned int>());
        for(auto const &c : x) {
            if (c != '\n') {
                m_values.back().push_back(c - '0');
            }
        }
    }
    rmax = m_values.size() - 1;
    cmax = m_values[0].size() - 1;
}



std::vector<Pos> getNbors(const Pos &u, unsigned int rmax, unsigned int cmax){
    std::vector<Pos> res;
    if (u.r != 0 && (u.d != SOUTH) && !(u.d == NORTH && u.d1 == NORTH && u.d2 == NORTH)) {
        res.push_back(Pos(u.r - 1, u.c, NORTH, u.d, u.d1));
    }
    if (u.c != cmax && (u.d != WEST) && !(u.d == EAST && u.d1 == EAST && u.d2 == EAST)) {
        res.push_back(Pos(u.r, u.c + 1, EAST, u.d, u.d1));
    }
    if (u.r != rmax && (u.d != NORTH) && !(u.d == SOUTH && u.d1 == SOUTH && u.d2 == SOUTH)) {
        res.push_back(Pos(u.r + 1, u.c, SOUTH, u.d, u.d1));
    }
    if (u.c != 0 && (u.d != EAST) && !(u.d == WEST && u.d1 == WEST && u.d2 == WEST)) {
        res.push_back(Pos(u.r, u.c - 1, WEST, u.d, u.d1));
    }
    return res;
}

unsigned int CrucibleMap::getShortestPath() {
    PosMap<unsigned int> dist(rmax, cmax);
    PosMapBool visited(rmax, cmax); // TODO: sfinae this into PosMap
    PosMap<Pos> prev(rmax, cmax);
    auto cmp = [&dist](const Pos &v1, const Pos &v2) { return dist[v1] < dist[v2]; };
    std::multiset<Pos, decltype(cmp)> q(cmp);
    for (unsigned int r = 0; r <= rmax; r++) {
        for (unsigned int c = 0; c <= cmax; c++) {
            for (unsigned int id = 0; id <= 4; id++) {
                for (unsigned int id1 = 0; id1 <= 4; id1++) {
                    for (unsigned int id2 = 0; id2 <= 4; id2++) {
                        Direction d = static_cast<Direction>(id);
                        Direction d1 = static_cast<Direction>(id1);
                        Direction d2 = static_cast<Direction>(id2);
                        dist[Pos(r, c, d, d1, d2)] = std::numeric_limits<unsigned int>::max();
                        prev[Pos(r, c, d, d1, d2)] = Pos(rmax + 1, cmax + 1, INVALID, INVALID, INVALID);
                        visited[Pos(r, c, d, d1, d2)] = false;
                    }
                }
            }
        }
    }
    auto u = Pos(0, 0, INVALID, INVALID, INVALID);
    dist[u] = 0;
    visited[u] = true;
    q.insert(u);
    while (!q.empty()) {
        u = *q.begin();
        q.erase(q.begin());
        if (u.r == rmax && u.c == cmax) {
            break; // done!
        }

        unsigned int alt;
        auto nbors = getNbors(u, rmax, cmax);
        for (auto v: nbors) {
            if(!visited[v]) {
                visited[v] = true;
                alt = dist[u] + m_values[v.r][v.c];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                }
                q.insert(v);
            }
        }
    }

    return dist[u];
}
