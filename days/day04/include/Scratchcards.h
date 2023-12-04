#pragma once
#include <vector>
#include <set>
#include <iostream>

class Scratchcards {
public:
    Scratchcards(std::istream &input);
    std::pair<unsigned int,unsigned int> getTotalScores();
private:
    unsigned int getScore(unsigned int i);
    std::vector<std::pair<std::set<unsigned int>, std::set<unsigned int>>> m_scratchcards;
    std::vector<unsigned int> m_copies;
};