#include "DesertMap.h"
#include <set>
#include <numeric>
DesertMap::DesertMap(std::istream &in) {
    std::string x;
    std::getline(in, x);
    for (unsigned int i = 0; i < x.size(); i++) {
        if (x[i] == 'L') m_instructions.push_back(0);
        else if (x[i] == 'R') m_instructions.push_back(1);
    }
    std::getline(in, x); // empty line
    while (std::getline(in, x)) {
        std::string node = x.substr(0, 3);
        m_map.push_back({std::array<unsigned int, 2>(), node == "ZZZ", node[2] == 'Z',
                         x.substr(7, 3), x.substr(12, 3), node});
    }
    for (unsigned int i = 0; i < m_map.size(); i++) {
        for (unsigned int j = 0; j < m_map.size(); j++) {
            if (m_map[j].lfull == m_map[i].nfull) { m_map[j].next[0] = i;}
            if (m_map[j].rfull == m_map[i].nfull) { m_map[j].next[1] = i;}
        }
        if (m_map[i].nfull == "AAA") { m_start_node = i;}
        if (m_map[i].nfull[2] == 'A') {m_starting_nodes.push_back(i);}
    }
}

unsigned int DesertMap::navigate() {
    unsigned int steps = 0;
    unsigned int loc = m_start_node;
    while (!m_map[loc].fullwin) {
        loc = m_map[loc].next[m_instructions[steps % m_instructions.size()]];
        steps++;
    }
    return steps;
}

unsigned long int DesertMap::navigateGhosts() {
    auto locs = m_starting_nodes;
    auto loops = std::vector<std::vector<std::pair<unsigned int, unsigned int>>>();
    auto loops_init_steps = std::vector<std::vector<unsigned long int>>();
    auto found_loops = std::set<unsigned int>();
    for (unsigned int i = 0; i < locs.size(); i++) {
        loops.push_back(std::vector<std::pair<unsigned int, unsigned int>>());
        loops_init_steps.push_back(std::vector<unsigned long int>());
    }
    unsigned long int steps = 0;
    while ( found_loops.size() != locs.size()) {
        unsigned int step = steps % m_instructions.size();
        for (unsigned int i = 0; i < locs.size(); i++) {
            if (found_loops.contains(i)) continue;
            locs[i] = m_map[locs[i]].next[m_instructions[step]];
            if (m_map[locs[i]].ghostwin) {
                auto globalloc = std::make_pair(locs[i], step);
                if (std::find(loops[i].begin(), loops[i].end(), globalloc) != loops[i].end()) {
                    found_loops.insert(i);
                }
                loops[i].push_back(globalloc);
                loops_init_steps[i].push_back(steps + 1);
            }
        }
        steps++;
    }
    //found our Zloops
    // Now we assume
    // - a simple loop (single z visited )
    // - Time to first loop is same as period
    // These are not guaranteed but seems true for inputs!
    std::vector<unsigned long int> periods;
    for (auto const &loop: loops_init_steps) {
        periods.push_back(loop[1] - loop[0]);
    }

    unsigned long int res = 1;
    for (auto const &p : periods) {
        res = std::lcm(p, res);
    }
    return res;
}