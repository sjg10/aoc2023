#pragma once
#include <iostream>
#include <vector>
#include <map>

using EdgeId = unsigned int;
using NodeId = unsigned int;

class WiringNode {
public:
    WiringNode(const std::string &name) : m_name(name) {};
    void addNbor(EdgeId id1, NodeId id2) {m_neighbours.push_back({id1,id2});};
    std::vector<std::pair<EdgeId, NodeId>> getNbors() const {return m_neighbours;};
    std::string getName() const {return m_name;};
    std::vector<std::pair<EdgeId, NodeId>>::const_iterator begin() const {
        return m_neighbours.begin();
    }
    std::vector<std::pair<EdgeId, NodeId>>::const_iterator end() const {
        return m_neighbours.end();
    }

private:
    std::string m_name;
    std::vector<std::pair<EdgeId, NodeId>> m_neighbours;
};

class WiringMachine {
public:
    WiringMachine(std::istream &in);
    unsigned int getScore();
private:
    unsigned int getComponents(EdgeId a, EdgeId b, EdgeId c);
    void getShortestPath(NodeId start, std::vector<unsigned int> &edge_occurence, EdgeId excla, EdgeId exclb);
    unsigned int getBusiestEdge(EdgeId excla, EdgeId exclb);
    std::map<std::string, unsigned int> m_node_map;
    std::vector<std::string> m_edges;
    std::vector<WiringNode> m_nodes;
};