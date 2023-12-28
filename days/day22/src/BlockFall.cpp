#include "BlockFall.h"
#include <regex>
#include <iostream>

Block::Block(const std::string &in) {
    std::regex rgx("(\\d*),(\\d*),(\\d*)~(\\d*),(\\d*),(\\d*)");
    std::smatch matches;
    std::regex_search(in, matches, rgx);
    m_xmin = std::stoul(matches[1].str());
    m_ymin = std::stoul(matches[2].str());
    m_zmin = std::stoul(matches[3].str());
    m_xmax = std::stoul(matches[4].str());
    m_ymax = std::stoul(matches[5].str());
    m_zmax = std::stoul(matches[6].str());
}



void Block::addSupporting(unsigned int i, std::vector<Block> &ordered_blocks) {
    bool supports = true;
    for (auto const &j : ordered_blocks[i].m_supported_by) {
        if (j != m_name && !m_total_supports.contains(j)) {
            supports = false;
            break;
        }
    }
    if (supports) {
        m_total_supports.insert(i);
    }
    for(auto &s: m_supported_by) {
        ordered_blocks[s].addSupporting(i, ordered_blocks);
    }
}


void Block::fall(unsigned int thisi, std::vector<Block> &ordered_blocks) {
    m_name = thisi;
    unsigned int targetz = 1;
    for(int j = thisi - 1; j >= 0; j--) {
        unsigned int next_targetz = ordered_blocks[j].m_zmax + 1;
        if (base_intersect(ordered_blocks[j]) && next_targetz >= targetz ) {
            if(next_targetz != targetz) {
                m_supported_by.clear();
            }
            targetz = next_targetz;
            m_supported_by.push_back(j);
        }
    }
    if (m_supported_by.size() == 1) {
        ordered_blocks[m_supported_by[0]].m_sole_supporter = true;
    }
    for (auto const &s : m_supported_by) {
        ordered_blocks[s].addSupporting(thisi, ordered_blocks);
    }
    unsigned int fall = m_zmin - targetz;
    m_zmin -= fall;
    m_zmax -= fall;
}


bool in_range(int value, int min, int max)
{ return (value >= min) && (value <= max); }



// return if the (x,y) plane base of this block intersects that of b
bool Block::base_intersect(const Block &b) const {
    bool x_intersect = in_range(m_xmin, b.m_xmin, b.m_xmax) || in_range(b.m_xmin, m_xmin, m_xmax);
    bool y_intersect = in_range(m_ymin, b.m_ymin, b.m_ymax) || in_range(b.m_ymin, m_ymin, m_ymax);
    return x_intersect && y_intersect;
}

BlockField::BlockField(std::istream &in) {
    for (std::string x; std::getline(in, x);) {
        m_blocks.emplace_back(Block(x));
    }
    std::sort(m_blocks.begin(), m_blocks.end(), Block::zcmp);
    for(unsigned int i = 0; i < m_blocks.size(); i++) {
        m_blocks[i].fall(i, m_blocks);
    }
}

std::pair<unsigned int,unsigned int> BlockField::getRemovable() {
    unsigned int removable = 0;
    unsigned int removable2 = 0;
    for (auto const &b: m_blocks) {
        if (!b.sole_support()) {
            removable++;
        }
        else {
            removable2 += b.support_total();
        }
    }
    return {removable, removable2};
}
