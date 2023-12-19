#include "MachineSort.h"
#include <regex>
#include <iostream>

std::ostream & operator<<(std::ostream &os, const PartRange &p) {
    for (auto const &r : p.m_ranges ) {
        for (unsigned int i = 0; i < 4; i ++ ) {
            os << "(" << r.first[i] << "," << r.second[i] << ") ";
        }
        os << std::endl;
    }
    return os;
}

PartRange::PartRange(const Part &start, const Part &end) {
    m_ranges.push_back({start, end});
}

void PartRange::rangeUnion(const PartRange &p) {
    m_ranges.insert(m_ranges.begin(), p.m_ranges.begin(), p.m_ranges.end());
}


std::pair<PartRange,PartRange> PartRange::split(unsigned int chr, unsigned int limit, bool lt) const {
    std::pair<PartRange,PartRange>  res = {PartRange() , PartRange()}; // good, bad
    for (auto const &r : m_ranges ) {
        if (lt) {
            if (r.second[chr] < limit) {
                res.first.rangeUnion(PartRange(r));
            } else if (r.first[chr] >= limit) {
                res.second.rangeUnion(PartRange(r));
            }
            else {
                Part mid = r.second;
                mid[chr] = limit - 1;
                res.first.rangeUnion(PartRange(r.first, mid));
                mid = r.first;
                mid[chr] = limit;
                res.second.rangeUnion(PartRange(mid, r.second));
            }
        }
        else {
            if (r.first[chr] > limit) {
                res.first.rangeUnion(PartRange(r));
            } else if (r.second[chr] <= limit) {
                res.second.rangeUnion(PartRange(r));
            }
            else {
                Part mid = r.second;
                mid[chr] = limit;
                res.second.rangeUnion(PartRange(r.first, mid));
                mid = r.first;
                mid[chr] = limit + 1;
                res.first.rangeUnion(PartRange(mid, r.second));
            }
        }
    }
    return res;
}

unsigned long int PartRange::size() {
    unsigned long int size = 0;
    for (auto const &r: m_ranges) {
        size += (
            (unsigned long int)((r.second[0] - r.first[0]) + 1) *
            (unsigned long int)((r.second[1] - r.first[1]) + 1) *
            (unsigned long int)((r.second[2] - r.first[2]) + 1) *
            (unsigned long int)((r.second[3] - r.first[3]) + 1)
        );
    }
    return size;
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

std::map<std::string, PartRange> Rule::apply(const PartRange &p) const {
    std::map<std::string, PartRange> ret;
    if (m_default) {
        ret[m_dest] = p;
        return ret;
    }
    else  {
        auto p2 = p.split(m_char,m_int, m_lt);
        ret[m_dest] = p2.first;
        ret[""] = p2.second;
        return ret;
    }
}


RuleSet::RuleSet(const std::string name, const std::string &in) : m_name(name) {
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


std::map<std::string, PartRange>  RuleSet::apply(const PartRange &p) const {
    PartRange s = p;
    std::map<std::string, PartRange> pm;
    for(auto const &r : m_rules) {
        auto x = r.apply(s);
        for(auto const &y : x) {
            if (y.first.empty()) {
                s = y.second;
            }
            else {
                if (!y.second.empty()) {
                    if (pm.contains(y.first)) {
                        pm[y.first].rangeUnion(y.second);
                    } else {
                        pm[y.first] = y.second;
                    }
                }
            }
        }
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

PartRange MachineSort::sortpriv(const std::map<std::string, PartRange> &m) {
    auto p = PartRange();
    for (auto &[key,val] : m) {
        if (key == "A") {
            p.rangeUnion(val);
        }
        else if (key != "R") {
            auto m2 = m_rules[key].apply(val);
            p.rangeUnion(sortpriv(m2));
        }
    }
    return p;
}

unsigned long int MachineSort::sort2() {
    return sortpriv({{"in", PartRange({1,1,1,1}, {4000,4000,4000,4000})}}).size();
}
