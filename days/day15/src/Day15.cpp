#include <iostream>
#include <string>
#include <numeric>
#include "Day15.h"
#include <array>

std::vector<std::string> Day15::run(std::ifstream &input) {
    std::vector<std::string> out;
    std::string read_line;
    getline(input, read_line);
    out.push_back(std::to_string(HASH(read_line)));
    out.push_back(std::to_string(HASH2(read_line)));
    return out;
}

unsigned int Day15::HASH(const std::string &x) {
    unsigned int ret = 0;
    unsigned char h = 0;
    for (auto const &c: x) {
        if (c == ',' || c == '\n') {
            ret += h;
            h = 0;
        } else {
            h += c;
            h *= 17;
        }
    }
    ret += h;
    return ret;
}

unsigned int Day15::HASH2(const std::string &x) {
    unsigned char box = 0;
    std::string label;
    std::array<std::vector<std::pair<std::string, unsigned int>>, 256> m_boxes;
    bool in_lens = false;
    for (auto const &c: x) {
        if (in_lens) {
            in_lens = false;
            unsigned int lens = c - '0';
            bool found_label = false;
            for(unsigned int i = 0; i < m_boxes[box].size(); i++) {
                if(m_boxes[box][i].first == label) {
                    m_boxes[box][i].second = lens;
                    found_label = true;
                    break;
                }
            }
            if(!found_label) {
                m_boxes[box].push_back({label, lens});
            }
        } else if (c == '-') {
            bool found_label = false;
            unsigned int i = 0;
            for(i = 0; i < m_boxes[box].size(); i++) {
                if(m_boxes[box][i].first == label) {
                    found_label = true;
                    break;
                }
            }
            if (found_label) {
                m_boxes[box].erase(m_boxes[box].begin() + i);
            }
            // remove last!
        } else if (c == '=') {
            //box found;
            in_lens = true;
        } else if (c == ',' || c == '\n') {
            // end of line
            box = 0;
            label = "";
        } else {
            box += c;
            box *= 17;
            label += c;
        }
    }

    //score
    unsigned int ret = 0;
    for(unsigned int i = 0;i < m_boxes.size(); i++) {
        for(unsigned int j = 0;j < m_boxes[i].size(); j++) {
            ret += (i + 1) * (j + 1) * m_boxes[i][j].second;
        }
    }
    return ret;
}
