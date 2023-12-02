#pragma once
#include <string>
class CubeGame {
public:
    CubeGame(const std::string &input);
    unsigned int comptaibleScore(unsigned int r, unsigned int g, unsigned int b);
    unsigned int powerScore() { return m_min_r * m_min_g * m_min_b;};
private:
    unsigned int m_id;
    unsigned int m_min_r;
    unsigned int m_min_g;
    unsigned int m_min_b;
};