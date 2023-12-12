#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <map>

class SpringRow {
public:
    SpringRow(const std::string &x);
    SpringRow repeat();
    unsigned long int getValidOptions(unsigned int str_offset = 0, unsigned int groups_offset = 0);
private:
    SpringRow() = default;
    std::vector<unsigned int> m_groups; // the set of groups to split into
    std::string m_str; // the map string
    // a record of getValidOptions results for each str_offset, groups_offset pair
    std::map<std::pair<unsigned int, unsigned int>, unsigned long int> m_poss_map;
};

class SpringMap {
public:
    SpringMap(std::istream &in);
    std::pair<unsigned int, unsigned long int> getValidOptionsSum();
private:
    std::vector<SpringRow> m_springs;
    std::vector<SpringRow> m_springs_long;
};