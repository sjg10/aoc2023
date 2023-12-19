#pragma once
#include <string>
#include <vector>
#include <map>

using Part = std::array<unsigned int, 4>;

class PartRange {
public:
    PartRange(const Part &start, const Part &end) : m_range_start(start), m_range_end(end) {};
    //PartRange(const std::pair<Part, Part> &p) {m_ranges.push_back(p);};
    PartRange() : m_empty(true) {};
    std::pair<PartRange,PartRange> split(unsigned int chr, unsigned int limit, bool lt) const;
    unsigned long int size() const;
    bool empty() const { return m_empty;};
    friend std::ostream & operator<<(std::ostream &os, const PartRange &p);
private:
    Part m_range_start;
    Part m_range_end;
    bool m_empty = false;
};

class Rule {
public:
    Rule(const std::string &in);
    std::string apply(const Part &p) const;
    std::tuple<std::string, PartRange, PartRange> apply(const PartRange &p) const;
private:
    bool m_lt;
    bool m_default = false;
    unsigned int m_char;
    unsigned int m_int;
    std::string m_dest;
};

class RuleSet {
public:
    RuleSet(const std::string &name, const std::string &in);
    RuleSet() {};
    std::string apply(const Part &p) const;
    std::map<std::string, PartRange> apply(const PartRange &p, unsigned long int &acnt) const;
private:
    std::string m_name;
    std::vector<Rule> m_rules;
};

class MachineSort {
public:
    MachineSort(std::istream &in);
    unsigned int sort();
    unsigned long int sort2();
private:
    unsigned long int sortpriv(const std::map<std::string, PartRange> &m);
    std::vector<Part> m_parts;
    std::map<std::string, RuleSet> m_rules;
};