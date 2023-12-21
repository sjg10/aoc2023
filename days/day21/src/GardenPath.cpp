#include "GardenPath.h"
#include <numeric>
#include <set>
#include  <iomanip>

GardenPath::GardenPath(std::istream &in) {
    unsigned int row = 0;
    unsigned int col = 0;
    for(std::string x; std::getline(in, x);) {
        m_distances.push_back(std::vector<unsigned int>());
        m_garden.push_back(std::vector<bool>());
        col = 0;
        for(auto const &c : x) {
            if (c == '.') {
                m_garden.back().push_back(true);
                m_distances.back().push_back(std::numeric_limits<unsigned int>::max());
            }
            else if (c == '#') {
                m_garden.back().push_back(false);
                m_distances.back().push_back(std::numeric_limits<unsigned int>::max());
            }
            else if (c == 'S') {
                m_garden.back().push_back(true);
                m_distances.back().push_back(0);
                m_start = {row, col};
            };
            col++;
        }
        row++;
    }
    m_rmax = row - 1;
    m_cmax = col - 1;
    dijkstra();
}

unsigned int GardenPath::getReachable(unsigned int path_length) {
    unsigned int ret = 0;
    for (auto const &v : m_distances) {
        for (auto const &x: v) {
            if (((x%2) == (path_length % 2)) && x <= path_length) { ret++; }
        }
    }
    return ret;
}

unsigned int GardenPath::neighbours(const Coord &c, std::array<Coord, 4> &nbors) const {
    unsigned int nborcnt = 0;
    if(c.first != 0 && m_garden[c.first - 1][c.second]) {
        nbors[nborcnt++] = {c.first - 1, c.second};
    }
    if(c.first != m_rmax && m_garden[c.first + 1][c.second]) {
        nbors[nborcnt++] = {c.first + 1, c.second};
    }
    if(c.second != 0 && m_garden[c.first][c.second - 1]) {
        nbors[nborcnt++] = {c.first, c.second - 1};
    }
    if(c.second != m_cmax && m_garden[c.first][c.second + 1]) {
        nbors[nborcnt++] = {c.first, c.second + 1};
    }
    return nborcnt;
}



void GardenPath::dijkstra() {
    std::vector<std::vector<bool>> visited;
    std::array<Coord, 4> possible_nbors;
    auto cmp = [this](const Coord &v1, const Coord &v2) {
        return m_distances[v1.first][v1.second] <  m_distances[v2.first][v2.second];
    };
    std::multiset<Coord, decltype(cmp)> q(cmp);
    for (unsigned int r = 0; r <= m_rmax; r++) {
        visited.push_back(std::vector<bool>(m_cmax + 1));
    }
    Coord u = m_start;
    m_distances[m_start.first][m_start.second] = 0;
    visited[m_start.first][m_start.second] = true;
    q.insert(u);
    while (!q.empty()) {
        u = *q.begin();
        q.erase(q.begin());

        unsigned int alt;
        auto nbors = neighbours(u, possible_nbors);
        for(unsigned int i = 0; i < nbors; i++) {
            auto v = possible_nbors[i];
            if(!visited[v.first][v.second]) {
                visited[v.first][v.second] = true;
                alt = m_distances[u.first][u.second] + 1;
                if (alt < m_distances[v.first][v.second]) {
                    m_distances[v.first][v.second] = alt;
                    //prev[v.first][v.second] = u;
                }
                q.insert(v);
            }
        }
    }
}
