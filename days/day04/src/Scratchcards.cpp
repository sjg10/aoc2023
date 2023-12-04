#include "Scratchcards.h"
#include <algorithm>
Scratchcards::Scratchcards(std::istream &input) {
    for(std::string x; std::getline(input, x);) {
        m_scratchcards.push_back({std::set<unsigned int>(), std::set<unsigned int>()});
        bool winners = true;
        size_t offset =  x.find(": ") + 1;
        do {
            offset = x.find_first_of(" |", offset + 1);
            if (offset == std::string::npos) {
                offset = x.size();
            }
            if(x[offset - 1] == '|') {
                winners = false;
                offset += 1;
                continue;
            }
            if(x[offset - 1] == ' ') continue;
            unsigned int val = std::stoul(x.substr(offset - 2 ,2));
            if (winners) {m_scratchcards.back().first.insert(val);}
            else {m_scratchcards.back().second.insert(val);}
        } while (offset != x.size());
    }
}

std::pair<unsigned int,unsigned int>  Scratchcards::getTotalScores() {
    unsigned int sum1 = 0;
    unsigned int sum2 = 0;
    m_copies = std::vector<unsigned int>(m_scratchcards.size(), 1);
    for (unsigned int i = 0; i < m_scratchcards.size(); i++) {
        sum1 += getScore(i);
    }
    for (unsigned int i = 0; i < m_copies.size(); i++) {
        sum2 += m_copies[i];
    }
    return {sum1,sum2};
}

unsigned int Scratchcards::getScore(unsigned int i) {
    std::set<unsigned int> intersection = std::set<unsigned int>();
    std::set_intersection(
        m_scratchcards[i].first.begin(),m_scratchcards[i].first.end(),
        m_scratchcards[i].second.begin(),m_scratchcards[i].second.end(),
        std::inserter(intersection, intersection.begin()));
    unsigned int matches = intersection.size();
    for (unsigned int j = i + 1; j <= i + matches; j++ ) {
        m_copies[j]+=m_copies[i];
    }
    return ((matches) == 0) ? 0 : (1 << (matches - 1));
};