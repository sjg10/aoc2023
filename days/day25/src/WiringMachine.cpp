#include "WiringMachine.h"
#include <queue>
#include <bitset>

WiringMachine::WiringMachine(std::istream &in) {
    for (std::string x; std::getline(in, x);) {
        std::string src = x.substr(0, 3);
        if (!m_node_map.contains(src)) {
            m_node_map[src]=m_nodes.size();
            m_nodes.push_back(WiringNode(src));
        }
        unsigned int n = 5;
        while( n < (x.size() - 1)) {
            std::string dest = x.substr(n, 3);
            if (!m_node_map.contains(dest)) {
                m_node_map[dest] = m_nodes.size();
                m_nodes.push_back(WiringNode(dest));
            }
            m_nodes[m_node_map[src]].addNbor(m_edges.size(), m_node_map[dest]);
            m_nodes[m_node_map[dest]].addNbor(m_edges.size(), m_node_map[src]);
            m_edges.push_back(src + "/" + dest);
            n+=4;
        }
    }
}

unsigned int WiringMachine::getScore() {
    // try visualised hint (using vis.py) first, will not cut any edges if not found
    unsigned int ret = 0;
    EdgeId ah = std::find(m_edges.begin(), m_edges.end(), "rrl/pcs") - m_edges.begin();
    EdgeId bh = std::find(m_edges.begin(), m_edges.end(), "qnd/mbk") - m_edges.begin();
    EdgeId ch = std::find(m_edges.begin(), m_edges.end(), "ddl/lcm") - m_edges.begin();
    ret = getComponents(ah, bh, ch);
    if (ret != 0) return ret;
    for(EdgeId a = 0; a < m_edges.size() -2; a++) {
        for (EdgeId b = a + 1; b < m_edges.size() - 1; b++) {
            for (EdgeId c = b + 1; c < m_edges.size(); c++) {
                ret = getComponents(a,b,c);
                if (ret != 0) return ret;
            }
        }
    }
    return 0;
}

unsigned int WiringMachine::getComponents(EdgeId a, EdgeId b, EdgeId c) {
    std::bitset<2048> visited; // at least as big as any input. quicker than vector bool
    std::vector<unsigned int> components;
    for ( unsigned int v = 0; v < m_nodes.size(); v++) {
        if(visited[v]) continue;
        else {
            components.push_back(0);
            std::queue<unsigned int> q;
            q.push(v);
            while (!q.empty()) {
                unsigned int u = q.front(); q.pop();
                if (visited[u]) continue;
                visited[u] = true;
                components.back()++;
                for (auto const &x: m_nodes[u]) {
                    if  (x.first != a && x.first != b && x.first != c) {
                        if (!visited[x.second]) {
                            q.push(x.second);
                        }
                    }
                }
            }
        }
    }
    return components.size() == 2 ? components[0] * components[1] : 0;
}
