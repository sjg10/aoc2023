#include "SpringMap.h"
#include <sstream>

unsigned long int SpringRow::getValidOptions(unsigned int str_offset, unsigned int groups_offset) {
    if (m_poss_map.contains({str_offset, groups_offset})) {
        return m_poss_map[{str_offset, groups_offset}];
    }
    unsigned long int ret = 0;
    // get how many chars left to fit into string
    unsigned int remsprings = 0;
    for (unsigned int i = groups_offset; i < m_groups.size(); i++) {
        remsprings += (m_groups[i] + 1); // springgroup + gap
    }
    remsprings--; // discount end gap
    bool last_group = (groups_offset == (m_groups.size() - 1));
    // if there are, try all the locations we can put the next group
    for (unsigned int i = str_offset; i < m_str.size(); i++) {
        if (m_str.size() - i < remsprings) {break;} // string too short to fit remaining in!
        bool good = true;
        for(unsigned int j = i; j < i + m_groups[groups_offset]; j++) {
            if (m_str[j] == '.') {
                good = false;
                break;
            }
        }
        if (good && !last_group && (m_str[i + m_groups[groups_offset]] == '#')) {
            good = false;
        }
        if (good) {
            if (!last_group) {
                ret += getValidOptions(
                      (i + m_groups[groups_offset] + 1),
                      groups_offset + 1
                      );
            }
            else {
                // if all placed but there is a # remaining we fail
                if (m_str.find('#', i + m_groups[groups_offset]) == std::string::npos) {ret++;}
            }
        }
        if (m_str[i] == '#') {break;} // cant start any later, as that discards a fixed spring!

    }
    m_poss_map[{str_offset, groups_offset}] = ret;
    return ret;
}

SpringRow::SpringRow(const std::string &x) {
    auto space = x.find(' ');
    m_str = x.substr(0, space);
    std::stringstream ss(x.substr(space + 1 ));
    for (unsigned int j; ss >> j;) {
        m_groups.push_back(j);
        if (ss.peek() == ',') {ss.ignore();}
    }
}

SpringRow SpringRow::repeat() {
    SpringRow sm = SpringRow();
    sm.m_str = m_str;
    sm.m_groups = m_groups;
    for (unsigned int i = 0; i < 4; i++) {
        sm.m_str = sm.m_str + '?' + m_str;
        sm.m_groups.insert(sm.m_groups.end(), m_groups.begin(), m_groups.end());
    }
    return sm;
}


SpringMap::SpringMap(std::istream &in) {
    for(std::string x; std::getline(in, x);) {
        m_springs.push_back(SpringRow(x));
        m_springs_long.push_back(m_springs.back().repeat());
    }
}

std::pair<unsigned int, unsigned long int> SpringMap::getValidOptionsSum() {
    unsigned int ret1 = 0;
    unsigned long int ret2 = 0;
    for(auto &s : m_springs) {
        auto x = s.getValidOptions();
        ret1 += x;
    }
    for(auto &s : m_springs_long) {
        auto x = s.getValidOptions();
        ret2 += x;
    }
    return {ret1, ret2};
}
