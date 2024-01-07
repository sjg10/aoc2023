#include "ForestWalk.h"
#include <map>

unsigned int
getNbors(const std::vector<std::vector<char>> &map, const Coord &l, const Coord &prev, std::array<Coord, 4> &nbors,
         bool slip) {
    unsigned int nborcnt = 0;
    char c = map[l.first][l.second];
    Coord next;
    if (slip && c == '^') {
        nbors[0] = {l.first - 1, l.second};
        return 1;
    } else if (slip && c == 'v') {
        nbors[0] = {l.first + 1, l.second};
        return 1;
    } else if (slip && c == '>') {
        nbors[0] = {l.first, l.second + 1};
        return 1;
    } else if (slip && c == '<') {
        nbors[0] = {l.first, l.second - 1};
        return 1;
    } else {
        next = {l.first - 1, l.second};
        try {
            if (next != prev && map.at(next.first).at(next.second) != '#') {
                nbors[nborcnt++] = next;
            }
        } catch (const std::out_of_range &oor) {}
        next = {l.first + 1, l.second};
        try {
            if (next != prev && map.at(next.first).at(next.second) != '#') {
                nbors[nborcnt++] = next;
            }
        } catch (const std::out_of_range &oor) {}
        next = {l.first, l.second + 1};
        try {
            if (next != prev && map.at(next.first).at(next.second) != '#') {
                nbors[nborcnt++] = next;
            }
        } catch (const std::out_of_range &oor) {}
        next = {l.first, l.second - 1};
        try {
            if (next != prev && map.at(next.first).at(next.second) != '#') {
                nbors[nborcnt++] = next;
            }
        } catch (const std::out_of_range &oor) {}
        return nborcnt;
    }
}


ForestWalk::ForestWalk(std::istream &in) {
    std::vector<std::vector<char>> map;
    for (std::string x; std::getline(in, x);) {
        map.push_back(std::vector<char>());
        for (auto const &c: x) {
            map.back().push_back(c);
        }
    }
    const Coord start = {0,1};
    const Coord end = {map.size() - 1, map[0].size() - 2};
    // Create nodes
    std::map<Coord, unsigned int> node_map;
    m_nodes.push_back(Node(start));
    m_start = 0;
    node_map[start] = m_start;
    m_nodes.push_back(Node(end));
    m_end = 1;
    node_map[end] = m_end;
    std::array<Coord, 4> nbors;
    for (unsigned int r = 1;
         r < map.size() - 1; r++) { // skip the first/last row as it has no nodes other than  start/end
        for (unsigned int c = 0; c < map[0].size(); c++) {
            if (getNbors(map, {r, c}, {0, 0}, nbors, false) > 2) {
                node_map[{r, c}] = m_nodes.size();
                m_nodes.push_back(Node({r, c}));
            }
        }
    }
    // Walk paths
    for (auto &n: m_nodes) {
        unsigned int dirs = getNbors(map, n.getLoc(), {0, 0}, nbors, false);
        for (unsigned int dir = 0; dir < dirs; dir++) {
            unsigned int dist = 1;
            Coord next = nbors[dir];
            Coord prev = n.getLoc();
            std::array<Coord, 4> nnbors;
            unsigned int ndirs = getNbors(map, next, prev, nnbors, false);
            while (ndirs == 1) {
                prev = next;
                next = nnbors[0];
                dist++;
                ndirs = getNbors(map, next, prev, nnbors, false);
            }
            if (ndirs != 0 || next == end) { // not a deadend or end
                n.addNbor(node_map[next], dist);
            }
        }
    }
    // Walk slip paths
    for (auto &n: m_nodes) {
        unsigned int dirs = getNbors(map, n.getLoc(), {0, 0}, nbors, true);
        for (unsigned int dir = 0; dir < dirs; dir++) {
            unsigned int dist = 1;
            Coord next = nbors[dir];
            Coord prev = n.getLoc();
            std::array<Coord, 4> nnbors;
            unsigned int ndirs = getNbors(map, next, prev, nnbors, true);
            while (ndirs == 1) {
                prev = next;
                next = nnbors[0];
                dist++;
                ndirs = getNbors(map, next, prev, nnbors, true);
            }
            if (ndirs != 0 || next == end) { // not a deadend or end
                n.addSlipNbor(node_map[next], dist);
            }
        }
    }
}

NodePath::NodePath(NodePath &t) {
    m_visited = t.m_visited;
    m_dist = t.m_dist;
    m_top = t.m_top;
}


unsigned int ForestWalk::getLongestPath(bool slip) {
    std::vector<std::shared_ptr<NodePath>> paths;
    std::vector<std::shared_ptr<NodePath>> newpaths;
    paths.emplace_back(std::make_shared<NodePath>(m_nodes.size(), m_start));
    std::vector<unsigned int> nbors;
    std::vector<unsigned int> dists;
    unsigned int best = 0;
    while (!paths.empty()) {
        for (auto p: paths) {
            m_nodes[p->top()].getNbors(nbors, slip);
            m_nodes[p->top()].getDists(dists, slip);
            for (unsigned int j = 0; j < nbors.size(); j++) {
                auto l = p->step(nbors[j], dists[j], m_end, newpaths);
                if (l > best) best = l;
            }
        }
        newpaths.swap(paths);
        newpaths.clear();
    }
    return best;
}