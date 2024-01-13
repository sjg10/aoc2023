#include "WiringMachine.h"
#include <queue>
#include <bitset>
#include <limits>
#include <set>

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

unsigned int WiringMachine::getBusiestEdge(EdgeId excla, EdgeId exclb) {
    std::vector<unsigned int> edge_occurence(m_edges.size());
    for (unsigned int i  =0; i < m_nodes.size(); i++) {
        getShortestPath(i, edge_occurence, excla, exclb);
    }
    std::vector<std::pair<unsigned int, unsigned int>> edge_occurence2(m_edges.size());
    for(unsigned int i = 0; i < m_edges.size(); i++) {
        edge_occurence2[i] = {i,edge_occurence[i]};
    }
    std::sort(edge_occurence2.begin(), edge_occurence2.end(),  [](const std::pair<unsigned int, unsigned int> &a, const std::pair<unsigned int, unsigned int> &b)
    {
        return a.second < b.second;
    });
    return edge_occurence2.rbegin()->first;
}

unsigned int WiringMachine::getScore() {
    EdgeId a = getBusiestEdge(std::numeric_limits<EdgeId>::max(),std::numeric_limits<EdgeId>::max());
    std::cout <<m_edges[a] <<std::endl;
    EdgeId b = getBusiestEdge(a, std::numeric_limits<EdgeId>::max());
    std::cout <<m_edges[b] <<std::endl;
    EdgeId c = getBusiestEdge(a,b);
    std::cout <<m_edges[c] <<std::endl;

    return getComponents(a,b,c);
}

unsigned int WiringMachine::getComponents(EdgeId a, EdgeId b, EdgeId c) {
    std::vector<bool> visited(m_nodes.size()); // at least as big as any input. quicker than vector bool
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

void WiringMachine::getShortestPath(NodeId start, std::vector<unsigned int> &edge_occurence, EdgeId excla, EdgeId exclb) {
    std::bitset<2048> visited; // at least as big as any input. quicker than vector bool
    std::vector<unsigned int> dist(m_nodes.size(), std::numeric_limits<unsigned int>::max());
    std::vector<std::pair<int, int>> prev(m_nodes.size(), {-1, -1});
    auto cmp = [&dist](unsigned int v1, unsigned int v2) { return dist[v1] < dist[v2]; };
    std::multiset<unsigned int, decltype(cmp)> q(cmp);
    auto u = start;
    dist[u] = 0;
    visited[u] = true;
    q.insert(u);
    while (!q.empty()) {
        u = *q.begin();
        q.erase(q.begin());

        unsigned int alt;
        for (auto const &v: m_nodes[u]) {
            if (v.first == excla || v.first == exclb ) { continue;}
            if(!visited[v.second]) {
                visited[v.second] = true;
                alt = dist[u] + 1;
                if (alt < dist[v.second]) {
                    dist[v.second] = alt;
                    prev[v.second] = {v.first, u};
                }
                q.insert(v.second);
            }
        }
    }
    for (auto const &x : prev) {
        if (x.first != -1) {
            edge_occurence[x.first]++;
        }
    }

}