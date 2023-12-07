#include "CamelCards.h"
#include <algorithm>
#include <map>

const std::map<char, unsigned int> card_map = {
    {'2',2},
    {'3',3},
    {'4',4},
    {'5',5},
    {'6',6},
    {'7',7},
    {'8',8},
    {'9',9},
    {'T',10},
    {'J',11},
    {'Q',12},
    {'K',13},
    {'A',14},
};

const std::map<char, unsigned int> card_map2 = {
    {'J',1},
    {'2',2},
    {'3',3},
    {'4',4},
    {'5',5},
    {'6',6},
    {'7',7},
    {'8',8},
    {'9',9},
    {'T',10},
    {'Q',12},
    {'K',13},
    {'A',14},
};

CamelHand::CamelHand(const std::string &in){
    m_bid = std::stoul(in.substr(6));
    m_freqs.fill(0);
    for(unsigned int i =0; i < 5; i++) {
        unsigned int card = card_map.at(in[i]);
        m_freqs[card]++;
        m_hand[i] = card;
    }
    std::sort(m_freqs.begin(), m_freqs.end(), std::greater<unsigned int>());
    if (m_freqs[0] == 5) {
        m_hand_worth = 6;
    } else if (m_freqs[0] == 4) {
        m_hand_worth = 5;
    } else if (m_freqs[0] == 3 && m_freqs[1] == 2)   {
        m_hand_worth = 4;
    } else if (m_freqs[0] == 3)   {
        m_hand_worth = 3;
    } else if (m_freqs[0] == 2 && m_freqs[1] == 2 )   {
        m_hand_worth = 2;
    } else if (m_freqs[0] == 2)   {
        m_hand_worth = 1;
    } else {
        m_hand_worth = 0;
    }
}

CamelHandJ::CamelHandJ(const std::string &in){
    m_bid = std::stoul(in.substr(6));
    m_freqs.fill(0);
    unsigned int jockers = 0;
    for(unsigned int i =0; i < 5; i++) {
        unsigned int card = card_map2.at(in[i]);
        if (card == 1) {jockers++;}
        else {m_freqs[card]++;} // exclude jockers from freqs
        m_hand[i] = card;
    }
    std::sort(m_freqs.begin(), m_freqs.end(), std::greater<unsigned int>());
    if ((m_freqs[0] + jockers) == 5) {
        m_hand_worth = 6;
    } else if ((m_freqs[0]  + jockers) == 4) {
        m_hand_worth = 5;
    } else if ((m_freqs[0] + jockers) >= 3 && (m_freqs[1] + ((jockers - (3 - m_freqs[0]))) >= 2)) {
        m_hand_worth = 4;
    } else if ((m_freqs[0] + jockers) == 3)   {
        m_hand_worth = 3;
    } else if ((m_freqs[0] + jockers) >= 2 && (m_freqs[1] + ((jockers - (2 - m_freqs[0]))) >= 2)) {
        m_hand_worth = 2;
    } else if ((m_freqs[0] + jockers) == 2)   {
        m_hand_worth = 1;
    } else {
        m_hand_worth = 0;
    }
}

bool operator== (const CamelHand& c1, const CamelHand& c2)
{
    return c1.m_hand_worth == c2.m_hand_worth &&
    c1.m_hand[0] == c2.m_hand[0] &&
    c1.m_hand[1] == c2.m_hand[1] &&
    c1.m_hand[2] == c2.m_hand[2] &&
    c1.m_hand[3] == c2.m_hand[3] &&
    c1.m_hand[4] == c2.m_hand[4];
}

bool operator< (const CamelHand& c1, const CamelHand& c2)
{
    if(c1.m_hand_worth != c2.m_hand_worth) {
        return c1.m_hand_worth < c2.m_hand_worth;
    }
    else if (c1.m_hand[0] != c2.m_hand[0]) {
        return c1.m_hand[0] < c2.m_hand[0];
    }
    else if (c1.m_hand[1] != c2.m_hand[1]) {
        return c1.m_hand[1] < c2.m_hand[1];
    }
    else if (c1.m_hand[2] != c2.m_hand[2]) {
        return c1.m_hand[2] < c2.m_hand[2];
    }
    else if (c1.m_hand[3] != c2.m_hand[3]) {
        return c1.m_hand[3] < c2.m_hand[3];
    }
    else if (c1.m_hand[4] != c2.m_hand[4]) {
        return c1.m_hand[4] < c2.m_hand[4];
    }
    return false;//equal!
}


CamelCards::CamelCards(std::istream &in) {
    for(std::string x; std::getline(in, x);) {
        m_hands.insert(CamelHand(x));
        m_handsJ.insert(CamelHandJ(x));
    }
    
}

unsigned int CamelCards::getScore(){
    unsigned int sum = 0;
    unsigned int rank = 1;
    for (auto const & itr : m_hands) {
        sum += (itr.getBid() * rank);
        rank++;
    }
    return sum;
}

unsigned int CamelCards::getScoreJ(){
    unsigned int sum = 0;
    unsigned int rank = 1;
    for (auto const & itr : m_handsJ) {
        sum += (itr.getBid() * rank);
        rank++;
    }
    return sum;
}