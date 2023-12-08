#pragma once
#include <iostream>
#include <map>
#include <array>
#include <vector>

struct DesertMapNode {
    std::array<unsigned int, 2> next;
    bool fullwin;
    bool ghostwin;
    std::string lfull;
    std::string rfull;
    std::string nfull;
};

class DesertMap {
public:
    DesertMap(std::istream &in);
    unsigned int navigate();
    unsigned long int navigateGhosts();
private:
    std::vector<unsigned int> m_instructions;
    std::vector<DesertMapNode> m_map;
    unsigned int m_start_node;
    std::vector<unsigned int> m_starting_nodes;
};