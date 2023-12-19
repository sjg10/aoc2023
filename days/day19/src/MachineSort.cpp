#include "MachineSort.h"
#include <regex>
#include <iostream>

std::pair<PartRange,PartRange> PartRange::split(unsigned int chr, unsigned int limit, bool lt) const {
    std::pair<PartRange,PartRange>  res = {PartRange() , PartRange()}; // good, bad
    if (lt) {
        if (m_range_end[chr] < limit) {
            res.first = *this;
        } else if (m_range_start[chr] >= limit) {
            res.second = *this;
        }
        else {
            Part mid = m_range_end;
            mid[chr] = limit - 1;
            res.first = PartRange(m_range_start, mid);
            mid = m_range_start;
            mid[chr] = limit;
            res.second = PartRange(mid, m_range_end);
        }
    }
    else {
        if (m_range_start[chr] > limit) {
            res.first = *this;
        } else if (m_range_end[chr] <= limit) {
            res.second = *this;
        }
        else {
            Part mid = m_range_end;
            mid[chr] = limit;
            res.second = PartRange(m_range_start, mid);
            mid = m_range_start;
            mid[chr] = limit + 1;
            res.first = PartRange(mid, m_range_end);
        }
    }
    return res;
}

unsigned long int PartRange::size() const{
    return
            (unsigned long int)((m_range_end[0] - m_range_start[0]) + 1) *
            (unsigned long int)((m_range_end[1] - m_range_start[1]) + 1) *
            (unsigned long int)((m_range_end[2] - m_range_start[2]) + 1) *
            (unsigned long int)((m_range_end[3] - m_range_start[3]) + 1);
}

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

std::tuple<std::string, PartRange, PartRange> Rule::apply(const PartRange &p) const {
    if (m_default) {
        return {m_dest, p, PartRange()};
    }
    else  {
        auto p2 = p.split(m_char,m_int, m_lt);
        return {m_dest, p2.first, p2.second};
    }
}


RuleSet::RuleSet(const std::string &name, const std::string &in) : m_name(name) {
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


std::map<std::string, PartRange> RuleSet::apply(const PartRange &p, unsigned long int &acnt) const {
    PartRange s = p;
    std::map<std::string, PartRange> pm;
    for(auto const &r : m_rules) {
        const auto[name, p1, p2] = r.apply(s);
        if(!p1.empty()) {
            if (name == "A") {
                acnt += p1.size();
            }
            else if (name != "R") {
                if (pm.contains(name)) {
                    throw std::runtime_error("runtime error");
                }
                pm[name] = p1;
            }
        }
        s = p2;
    }
    return pm;
}


MachineSort::MachineSort(std::istream &in) {
    bool in_rules = true;
    std::regex rgx("x=(\\d*),m=(\\d*),a=(\\d*),s=(\\d*)");
    std::smatch matches;
    for(std::string x; std::getline(in, x);) {
        if (x.empty()) in_rules = false;
        else if (in_rules) {
            auto off = x.find("{");
            std::string name = x.substr(0, off);
            m_rules[name] = RuleSet(name, x.substr(off));
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
        do {
            r = m_rules[r].apply(p);
        } while(r!= "R" && r != "A");
        if (r == "A") {
            ret += p[0];
            ret += p[1];
            ret += p[2];
            ret += p[3];
        }
    }
    return ret;
}

unsigned long int MachineSort::sortpriv(const std::map<std::string, PartRange> &m) {
    unsigned long int ret = 0;
    for (auto &[key,val] : m) {
        auto m2 = m_rules[key].apply(val, ret);
        ret += sortpriv(m2);
    }
    return ret;
}

unsigned long int MachineSort::sort2() {
    return sortpriv({{"in", PartRange({1,1,1,1}, {4000,4000,4000,4000})}});
}
