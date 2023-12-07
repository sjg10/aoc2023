#pragma once
#include <string>
#include <iostream>
#include <set>
#include <array>

class CamelHand {
public:
    CamelHand() {};
    CamelHand(const std::string &in);
    unsigned int getBid() const {return m_bid;}
    friend bool operator< (const CamelHand& c1, const CamelHand& c2);
    friend bool operator== (const CamelHand& c1, const CamelHand& c2);
protected:
    unsigned int m_bid;
    std::array<unsigned int, 5> m_hand;
    unsigned int m_hand_worth;
    std::array<unsigned int,15> m_freqs;
};

class CamelHandJ : public CamelHand {
public:
    CamelHandJ(const std::string &in);
};

class CamelCards {
public:
    CamelCards(std::istream &in);
    unsigned int getScore();
    unsigned int getScoreJ();
private:
    std::set<CamelHand> m_hands;
    std::set<CamelHandJ> m_handsJ;
};