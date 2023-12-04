#include "Scratchcards.h"
#include <algorithm>
Scratchcards::Scratchcards(std::istream &input) {
    for(std::string x; std::getline(input, x);) {
        std::set<unsigned int> winnumbers;
        bool winners = true; // currently reading winners
        m_scratchcards.push_back(0);
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
            if (winners) {winnumbers.insert(val);}
            else if (winnumbers.find(val) != winnumbers.end()) {
                m_scratchcards.back()++;
            }
        } while (offset != x.size());
    }
}

std::pair<unsigned int,unsigned int>  Scratchcards::getTotalScores() {
    unsigned int sum1 = 0;
    unsigned int sum2 = 0;
    unsigned int total_games = m_scratchcards.size();
    std::vector<unsigned int> copies(total_games, 1);
    for (unsigned int i = 0; i < total_games; i++) {
        unsigned int matches = m_scratchcards[i];
        sum1 += ((matches) == 0) ? 0 : (1 << (matches - 1));
        for (unsigned int j = i + 1; j <= i + matches; j++ ) {
            copies[j]+=copies[i];
        }
        sum2 += copies[i];
    }
    return {sum1,sum2};
}
