#include "MachineSort.h"
#include <regex>
#include <iostream>

Rule::Rule(const std::string &in) {
    if(in.find(":") == std::string::npos) {
        m_default = true;
        m_dest = in;
    }
    else {
        std::regex rgx("(.*)([><])(\\d*):(.*)");
        std::smatch matches;
        std::regex_search(in, matches, rgx);
        switch (matches[1].str()[0]) {
            case 'x': m_char = 0; break;
            case 'm': m_char = 1; break;
            case 'a': m_char = 2; break;
            case 's': m_char = 3; break;
            default: std::runtime_error("Unknown param");
        }
        m_lt = (matches[2].str()[0] == '<');
        m_int = std::stoul(matches[3].str());
        m_dest = (matches[4].str());
    }
}

std::string Rule::apply(const Part &p) const {
    if (m_default) {
        return m_dest;
    }
    else if (m_lt) {
        return  (p[m_char] < m_int)  ? m_dest : "";
    }
    else {
        return  (p[m_char] > m_int)  ? m_dest : "";
    }
}

RuleSet::RuleSet(const std::string &in){
    size_t offset = 1;
    size_t noffset = 1;
    noffset = in.find(",", offset);
    while(noffset != std::string::npos) {
        m_rules.emplace_back(Rule(in.substr(offset, noffset - offset)));
        offset = noffset + 1;
        noffset = in.find(",", offset);
    }
    m_rules.emplace_back(Rule(in.substr(offset, in.size() - (offset + 1))));
}

std::string RuleSet::apply(const Part &p) const {
    for(auto const &r : m_rules) {
        auto x = r.apply(p);
        if (!x.empty()) {return x;}
    }
    throw std::runtime_error("Missing default");
}

MachineSort::MachineSort(std::istream &in) {
    bool in_rules = true;
    std::regex rgx("x=(\\d*),m=(\\d*),a=(\\d*),s=(\\d*)");
    std::smatch matches;
    for(std::string x; std::getline(in, x);) {
        if (x.empty()) in_rules = false;
        else if (in_rules) {
            auto off = x.find("{");
            m_rules[x.substr(0, off)] = RuleSet(x.substr(off));
        }
        else {
            std::regex_search(x, matches, rgx);
            unsigned int xi = std::stoul(matches[1].str());
            unsigned int mi = std::stoul(matches[2].str());
            unsigned int ai = std::stoul(matches[3].str());
            unsigned int si = std::stoul(matches[4].str());
            m_parts.push_back({xi,mi,ai,si});
        }
    }
}
unsigned int MachineSort::sort() {
    unsigned int ret = 0;
    for(auto const &p: m_parts) {
        std::string r = "in";
//        std::cout << r << "->";
        do {
            r = m_rules[r].apply(p);
//            std::cout << r << "->";
        } while(r!= "R" && r != "A");
//        std::cout <<std::endl;
        if (r == "A") {
            ret += p[0];
            ret += p[1];
            ret += p[2];
            ret += p[3];
        }
    }
    return ret;
}
