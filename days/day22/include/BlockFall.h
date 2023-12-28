#pragma once
#include <string>
#include <vector>
#include <set>

class Block {
public:
    Block(const std::string &in);
    // have block fall as far as possible.
    // input is all blocks ordered by increasing zmin, this i is index of self
    void fall(unsigned int thisi, std::vector<Block> &ordered_blocks);
    // return if the (x,y0 plane base of this block intersects that of b
    bool base_intersect(const Block &b) const;
    unsigned int support_total() const { return m_total_supports.size(); }
    bool sole_support() const {return m_sole_supporter;};
    static bool zcmp(const Block &a, const Block &b) {return a.m_zmin < b.m_zmin;};
private:
    void addSupporting(unsigned int i, std::vector<Block> &ordered_blocks);
    unsigned int m_xmin;
    unsigned int m_xmax;
    unsigned int m_ymin;
    unsigned int m_ymax;
    unsigned int m_zmin;
    unsigned int m_zmax;
    std::vector<unsigned int> m_supported_by;
    std::set<unsigned int> m_total_supports;
    bool m_sole_supporter = false;
    unsigned int m_name = 10000;
};

class BlockField {
public:
    BlockField(std::istream &in);
    std::pair<unsigned int,unsigned int> getRemovable();
private:
    std::vector<Block> m_blocks;
};