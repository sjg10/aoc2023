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
    return os << pm.cur_run_length << ")";
}

template <class T>
PosMap<T>::PosMap(unsigned int rmax, unsigned int cmax) : rmax(rmax), cmax(cmax) {
    m_container = std::vector<T>((rmax + 1) * (cmax + 1) * 5 * (MAX_POSSIBLE_RUN_LENGTH + 1));
}

template <class T>
unsigned int PosMap<T>::getOffset(const Pos &p) {
    return
            (p.r * (5 * (MAX_POSSIBLE_RUN_LENGTH + 1) * (cmax + 1))) +
            (p.c * 5 * (MAX_POSSIBLE_RUN_LENGTH + 1)) +
            (p.d * (MAX_POSSIBLE_RUN_LENGTH + 1)) +
            p.cur_run_length;
}

template<class T> template<class Q> typename std::enable_if<std::is_same<Q, bool>::value, std::_Bit_reference>::type
PosMap<T>::operator[](const Pos &p) {
    return m_container[getOffset(p)];
}

template<class T> template<class Q> typename std::enable_if<!std::is_same<Q, bool>::value, Q&>::type
PosMap<T>::operator[](const Pos &p) {
    return m_container[getOffset(p)];
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



std::vector<Pos> getNbors(const Pos &u, unsigned int minrun, unsigned int maxrun, unsigned int rmax, unsigned int cmax){
    std::vector<Pos> res;
    if (u.r != 0 && (u.d != SOUTH) && !(u.d == NORTH && u.cur_run_length >= maxrun) && (u.d == NORTH || u.cur_run_length >= minrun || u.d == INVALID)) {
        res.push_back(Pos(u.r - 1, u.c, NORTH, u.d == NORTH ? u.cur_run_length + 1 : 1));
    }
    if (u.c != cmax && (u.d != WEST) && !(u.d == EAST && u.cur_run_length >= maxrun) && (u.d == EAST || u.cur_run_length >= minrun|| u.d == INVALID)) {
        res.push_back(Pos(u.r, u.c + 1, EAST, u.d == EAST ? u.cur_run_length + 1 : 1));
    }
    if (u.r != rmax && (u.d != NORTH) && !(u.d == SOUTH && u.cur_run_length >= maxrun) && (u.d == SOUTH || u.cur_run_length >= minrun|| u.d == INVALID)) {
        res.push_back(Pos(u.r + 1, u.c, SOUTH, u.d == SOUTH ? u.cur_run_length + 1 : 1));
    }
    if (u.c != 0 && (u.d != EAST) && !(u.d == WEST && u.cur_run_length >= maxrun) && (u.d == WEST || u.cur_run_length >= minrun || u.d == INVALID)) {
        res.push_back(Pos(u.r, u.c - 1, WEST, u.d == WEST ? u.cur_run_length + 1 : 1));
    }
    return res;
}

unsigned int CrucibleMap::getShortestPath(unsigned int minrun, unsigned int maxrun) {
    PosMap<unsigned int> dist(rmax, cmax);
    PosMap<bool> visited(rmax, cmax);
    PosMap<Pos> prev(rmax, cmax);
    auto cmp = [&dist](const Pos &v1, const Pos &v2) { return dist[v1] < dist[v2]; };
    std::multiset<Pos, decltype(cmp)> q(cmp);
    for (unsigned int r = 0; r <= rmax; r++) {
        for (unsigned int c = 0; c <= cmax; c++) {
            for (unsigned int id = 0; id <= 4; id++) {
                for (unsigned int rl = 0; rl <= MAX_POSSIBLE_RUN_LENGTH; rl++) {
                        Direction d = static_cast<Direction>(id);
                        dist[Pos(r, c, d, rl)] = std::numeric_limits<unsigned int>::max();
                        prev[Pos(r, c, d, rl)] = Pos(rmax + 1, cmax + 1, INVALID, 0);
                        visited[Pos(r, c, d, rl)] = false;
                }
            }
        }
    }
    auto u = Pos(0, 0, INVALID, 0);
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
        auto nbors = getNbors(u, minrun, maxrun, rmax, cmax);
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
