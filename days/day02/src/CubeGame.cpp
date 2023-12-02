#include "CubeGame.h"
#include <stdexcept>
#include <iostream>

CubeGame::CubeGame(const std::string &input) {
    m_min_r = 0;
    m_min_g = 0;
    m_min_b = 0;
    size_t cur_loc = input.find(":");
    size_t last_loc = cur_loc;
    m_id = std::stoul(input.substr(5, cur_loc));
    do {
        cur_loc = input.find_first_of(",;", last_loc + 1);
        unsigned int cnt = 0;
        std::string sub = input.substr(last_loc + 1, cur_loc - (last_loc + 1));
        cnt = std::stoul(sub);
        switch (sub[sub.length() - 1]) {
            case 'd': 
                if (cnt > m_min_r) m_min_r = cnt;
                break;
            case 'n':
                if (cnt > m_min_g) m_min_g = cnt;
                break;
            case 'e':
                if (cnt > m_min_b) m_min_b = cnt;
                break;
            default: throw std::runtime_error("Invalid"); break;
        }
        last_loc = cur_loc;
    } while (cur_loc != std::string::npos);
}

unsigned int CubeGame::comptaibleScore(unsigned int r, unsigned int g, unsigned int b){
    return (r >= m_min_r && g >= m_min_g && b >= m_min_b) ? m_id : 0;
}