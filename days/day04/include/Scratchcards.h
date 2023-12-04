#pragma once
#include <vector>
#include <set>
#include <iostream>

class Scratchcards {
public:
    Scratchcards(std::istream &input);
    std::pair<unsigned int,unsigned int> getTotalScores();
private:
    /** Number of winning numbers per scratchcard*/
    std::vector<unsigned int> m_scratchcards;
};