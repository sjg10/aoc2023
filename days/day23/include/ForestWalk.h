#pragma once
#include <vector>
#include <array>
#include <iostream>
#include <memory>

using Coord = std::pair<unsigned int, unsigned int>;

class Node {
public:
    Node(const Coord &c) : m_loc(c) {};
    void addNbor(unsigned int n, unsigned int d) {m_neighbours.push_back(n); m_dists.push_back(d);};
    void addSlipNbor(unsigned int n, unsigned int d) {m_slip_neighbours.push_back(n); m_slip_dists.push_back(d);};
    void getNbors(std::vector<unsigned int> &nbors, bool slip) {nbors = slip ? m_slip_neighbours : m_neighbours;};
    void getDists(std::vector<unsigned int> &dists, bool slip) {dists = slip ? m_slip_dists : m_dists;};
    Coord getLoc() {return m_loc;};
private:
    const Coord m_loc;
    std::vector<unsigned int> m_neighbours;
    std::vector<unsigned int> m_dists;
    std::vector<unsigned int> m_slip_neighbours;
    std::vector<unsigned int> m_slip_dists;
};


class NodePath {
public:
    NodePath(unsigned int total_nodes, unsigned int start) : m_dist(0), m_top(start) {m_visited = std::vector<bool>(total_nodes); m_visited[start] = true;};
    NodePath(NodePath &t);
    unsigned int top() const {return m_top;};
    unsigned int step(unsigned int i, unsigned int d, unsigned int end, std::vector<std::shared_ptr<NodePath>> &node_paths) {
        if (i == end) {
            return m_dist + d;
        }
        else if (!m_visited[i]) {
            node_paths.push_back(std::make_shared<NodePath>(*this));
            node_paths.back()->m_visited[i] = true;
            node_paths.back()->m_top = i;
            node_paths.back()->m_dist += d;
        }
        return 0;
    }
private:
    std::vector<bool> m_visited;
    unsigned int m_dist;
    unsigned int m_top;
};

class ForestWalk {
public:
    ForestWalk(std::istream &in);
    unsigned int getLongestPath(bool slip=true);
private:
    std::vector<Node> m_nodes;
    unsigned int m_start;
    unsigned int m_end;
};
