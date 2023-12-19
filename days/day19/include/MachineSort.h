#pragma once
#include <string>
#include <vector>
#include <map>

using Part = std::array<unsigned int, 4>;

class Rule {
public:
    Rule(const std::string &in);
    std::string apply(const Part &p) const;
private:
    bool m_lt;
    bool m_default = false;
    unsigned int m_char;
    unsigned int m_int;
    std::string m_dest;
};

class RuleSet {
public:
    RuleSet(const std::string &in);
    RuleSet() {};
    std::string apply(const Part &p) const;
private:
    std::vector<Rule> m_rules;
};

class MachineSort {
public:
    MachineSort(std::istream &in);
    unsigned int sort();
private:
    std::vector<Part> m_parts;
    std::map<std::string, RuleSet> m_rules;
};