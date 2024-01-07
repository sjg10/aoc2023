#include "HailStorm.h"
#include <regex>

const std::regex Hail::rgx = std::regex("([-]*\\d+),[ ]+([-]*\\d+),[ ]+([-]*\\d+)[ ]+@[ ]+([-]*\\d+),[ ]+([-]*\\d+),[ ]+([-]*\\d+)");

Hail::Hail(const std::string &in) {
    std::smatch matches;
    std::regex_search(in, matches, rgx);
    m_position[0] = std::stol(matches[1].str());
    m_position[1] = std::stol(matches[2].str());
    m_position[2] = std::stol(matches[3].str());
    m_velocity[0] = std::stol(matches[4].str());
    m_velocity[1] = std::stol(matches[5].str());
    m_velocity[2] = std::stol(matches[6].str());
}

Vector3DF Hail::getCollision(const Hail &h) const {
    // Note no zero v components!
    if (m_velocity[1] * h.m_velocity[0] == m_velocity[0] * h.m_velocity[1]) {
        // parallel!
        return {0,0,0};
    }
    else  {
        // summit is wrong
        double vB_ratio = (double)h.m_velocity[0] / (double)h.m_velocity[1];
        double tA =
                (double)(h.m_position[0] - m_position[0]) -
                        ((double)(h.m_position[1] - m_position[1]) * vB_ratio);
        tA /= ((double)m_velocity[0] - ((double)m_velocity[1] * vB_ratio));

        double vA_ratio = (double)m_velocity[0] / (double)m_velocity[1];
        double tB =
                ((double)(h.m_position[1] - m_position[1]) * vA_ratio) -
                (double)(h.m_position[0] - m_position[0]);
        tB /= ((double)h.m_velocity[0] - ((double)h.m_velocity[1] * vA_ratio));

        if(tA > 0 && tB > 0) {
            return {(double)m_position[0] + tA * (double)m_velocity[0] ,(double)m_position[1] + tA * (double)m_velocity[1], 0 };
        }
        else {
            return {0,0,0};
        }
    }
}


HailStorm::HailStorm(std::istream &in) {
    for(std::string x; std::getline(in, x);) {
        m_hail.push_back(Hail(x));
    }
}

unsigned int HailStorm::getCollisions(long int dmin, long int dmax) {
    unsigned int ret = 0;
    for (unsigned int i = 0; i < m_hail.size() - 1; i++) {
        for (unsigned int j = i + 1; j < m_hail.size(); j++) {
            auto v = m_hail[i].getCollision(m_hail[j]);
            if (v[0] >= dmin && v[0] <= dmax && v[1] >= dmin && v[1] <= dmax) {
                ret++;
            }
        }
    }
    return ret;
}
