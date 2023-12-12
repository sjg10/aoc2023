#pragma once
#include <vector>
#include <iostream>
#include <string>

class SpringRow {
public:
    SpringRow(const std::string &x);
    SpringRow repeat();
    unsigned long int getValidOptions() const;
private:
    SpringRow() = default;
    bool isValid(std::vector<bool> springs) const;
    std::vector<bool> m_springs;
    std::vector<unsigned int> m_damaged_spaces;
    std::vector<unsigned int> m_groups;
    unsigned int m_total_springs = 0;
    unsigned int m_fixed_spring_cnt = 0;
};

class SpringMap {
public:
    SpringMap(std::istream &in);
    std::pair<unsigned int, unsigned long int> getValidOptionsSum();
private:
    std::vector<SpringRow> m_springs;
    std::vector<SpringRow> m_springs_long;
};