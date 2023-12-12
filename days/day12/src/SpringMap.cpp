#include "SpringMap.h"
#include <sstream>
#include <set>

SpringRow::SpringRow(const std::string &x) {
    unsigned int i = 0;
    bool first_group = true;
    for (i = 0; i < x.size() && first_group; i++) {
        switch (x[i]) {
            case '#':
                m_springs.push_back(true);
                m_fixed_spring_cnt++;
                break;
            case '?':
                m_springs.push_back(false);
                m_damaged_spaces.push_back(i);
                break;
            case '.':
                m_springs.push_back(false);
                break;
            case ' ':
                first_group = false;
                break;
        }
    }

    std::stringstream ss(x.substr(i ));
    for (unsigned int j; ss >> j;) {
        m_groups.push_back(j);
        m_total_springs += j;
        if (ss.peek() == ',') {ss.ignore();}
    }
}

SpringRow SpringRow::repeat() {
    SpringRow sm = SpringRow();
    sm.m_springs = m_springs;
    sm.m_damaged_spaces = m_damaged_spaces;
    sm.m_total_springs = m_total_springs * 5;
    sm.m_fixed_spring_cnt = m_fixed_spring_cnt * 5;
    sm.m_groups = m_groups;
    for (unsigned int i = 0; i < 4; i++) {
        sm.m_damaged_spaces.push_back(sm.m_springs.size());
        for (auto const &x: m_damaged_spaces) {
            sm.m_damaged_spaces.push_back(x + sm.m_springs.size() + 1);
        }
        sm.m_springs.push_back(false);
        sm.m_springs.insert(sm.m_springs.end(), m_springs.begin(), m_springs.end());
        sm.m_groups.insert(sm.m_groups.end(), m_groups.begin(), m_groups.end());
    }
    return sm;
}

std::ostream& operator<<(std::ostream &os, const std::vector<bool> &v) {
    for (auto x:v) {
        os << (x ? "#" : ".") ;
    }
    return os;
}

unsigned long int SpringRow::getValidOptions() const {
    unsigned long int ret = 0;
    unsigned int springs_to_add = m_total_springs - m_fixed_spring_cnt;
    std::vector<bool> v(m_damaged_spaces.size());
    std::fill(v.begin(), v.begin() + springs_to_add, true);
    do {
        std::vector<bool> test_row = m_springs;
        for (unsigned int i = 0; i < m_damaged_spaces.size(); ++i) {
            if (v[i]) {
                test_row[m_damaged_spaces[i]] = true;
            }
        }
        if (isValid(test_row)) ret++;
    } while (std::prev_permutation(v.begin(), v.end()));
    return ret;
}


bool SpringRow::isValid(std::vector<bool> springs) const {
    unsigned int cur_group_size = 0;
    unsigned int cur_group_cnt = 0;
    bool in_group = false;
    for(unsigned int i = 0; i < springs.size(); i++) {
        if(springs[i]) {
            in_group = true;
            cur_group_size++;
        }
        if(!springs[i] && in_group) {
            in_group = false;
            if (cur_group_size != m_groups[cur_group_cnt]) {return false;}
            cur_group_cnt++;
            cur_group_size = 0;
        }
    }
    if (in_group) {
        in_group = false;
        if (cur_group_size != m_groups[cur_group_cnt]) {return false;}
        cur_group_cnt++;
        cur_group_size = 0;
    }
    if(cur_group_cnt != m_groups.size()) {return false;}
    else {
        return true;
    }
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
    for(auto const &s : m_springs) {
        ret1 += s.getValidOptions();
    }
    /*for(auto const &s : m_springs_long) {
        ret2 += s.getValidOptions();
    }*/
    return {ret1, ret2};
}
