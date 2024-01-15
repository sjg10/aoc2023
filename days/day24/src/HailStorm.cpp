#include "HailStorm.h"
#include <regex>
#include <set>
#include <limits>
#include <cassert>

const std::regex Hail::rgx = std::regex(
        "([-]*\\d+),[ ]+([-]*\\d+),[ ]+([-]*\\d+)[ ]+@[ ]+([-]*\\d+),[ ]+([-]*\\d+),[ ]+([-]*\\d+)");

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


bool Hail::getCollision(const Hail &h, double &x, double &y) const {
    if (h.getVel(0) == 0 || getVel(1) == 0) { return false; }
    long int det =
            getVel(1) * h.getVel(0) - h.getVel(1) * getVel(0);
    if (det == 0) { return false;}
    double t0 = double(h.getVel(0) * (h.getPos(1) - getPos(1)) +
            h.getVel(1) * (getPos(0) - h.getPos(0))) / (double)det;
    double t1 = ((double)(getPos(0) - h.getPos(0)) + ((double)getVel(0)* t0)) / (double)h.getVel(0);
    if (t0 > 0 && t1 > 0) {
        x = (double) getPos(0) + t0 * (double) getVel(0);
        y = (double) getPos(1) + t0 * (double) getVel(1);
        assert(std::abs(t0 - t1) > 0.00001); // just double check the input never has things meet even in 2d
        return true;
    }
    return false;
}


HailStorm::HailStorm(std::istream &in) {
    for (std::string x; std::getline(in, x);) {
        m_hail.push_back(Hail(x));
    }
    t.resize(m_hail.size());
}

unsigned int HailStorm::getCollisions(long int dmin, long int dmax) {
    unsigned int ret = 0;
    double x, y;
    for (unsigned int i = 0; i < m_hail.size() - 1; i++) {
        for (unsigned int j = i + 1; j < m_hail.size(); j++) {
            auto v = m_hail[i].getCollision(m_hail[j], x, y);
            if (v && x >= (double)dmin && x <= (double)dmax && y >= (double)dmin && y <= (double)dmax) {
                ret++;
            }
        }
    }
    return ret;
}

bool HailStorm::solveCollisions(unsigned int i, unsigned int j, long int vx, long int vy, Vector3D &pos) {
    double uxi = vx - m_hail[i].getVel(0);
    double uyi = vy - m_hail[i].getVel(1);
    double uxj = vx - m_hail[j].getVel(0);
    double uyj = vy - m_hail[j].getVel(1);
    // compare these two x,y,t lines for i and j and solve for x,y
    if (uxi == 0 || uxj == 0 || (uyi * uxj - uyj * uxi) == 0) { return false; }
    long int x = (long int) (
            (m_hail[j].getPos(1) - m_hail[i].getPos(1)) * uxi * uxj +
            m_hail[i].getPos(0) * uyi * uxj -
            m_hail[j].getPos(0) * uyj * uxi
    ) / (uyi * uxj - uyj * uxi);
    long int y = m_hail[i].getPos(1) - (uyi * (m_hail[i].getPos(0) - x)) / uxi;
    // Use these x,y to solve for t
    for (unsigned int k = 0; k < m_hail.size(); k++) {
        if ((vx - m_hail[k].getVel(0)) != 0) {
            t[k] = (m_hail[k].getPos(0) - x) / (vx - m_hail[k].getVel(0));
        } else if (vy - m_hail[k].getVel(1) != 0) {
            t[k] = (m_hail[k].getPos(1) - y) / (vy - m_hail[k].getVel(1));
        } else { return false; }
        if (t[k] <= 0) { return false; } // need +ive k
    }
    // Then use these t's to find vz and z
    long int vz = 0;
    bool foundvz = false;
    for (unsigned int k = 0; k < m_hail.size() - 1 && !foundvz; k++) {
        for (unsigned int l = k + 1; l < m_hail.size() && !foundvz; l++) {
            if ((t[l] - t[k]) != 0) {
                vz =
                        ((m_hail[l].getPos(2) + t[l] * m_hail[l].getVel(2)) -
                         (m_hail[k].getPos(2) + t[k] * m_hail[k].getVel(2))) / (t[l] - t[k]);
                foundvz = true;
            }
        }
    }
    if (!foundvz) { return false; }
    long int z =
            m_hail[0].getPos(2) + t[0] * m_hail[0].getVel(2) - t[0] * vz;
    // Finally sub x,y,z , vx,vy,vz back to each hailstone to validate
    for (unsigned int k = 1; k < m_hail.size(); k++) {
        if (((m_hail[k].getPos(2) + (t[k] * m_hail[k].getVel(2))) - (t[k] * vz)) != z) {
            return false;
        }
        if (((m_hail[k].getPos(1) + (t[k] * m_hail[k].getVel(1))) - (t[k] * vy)) != y) {
            return false;
        }
        if (((m_hail[k].getPos(0) + (t[k] * m_hail[k].getVel(0))) - (t[k] * vx)) != x) {
            return false;
        }
    }
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    return true;
}

long int HailStorm::getRock() {
    Vector3D pos;
    for (auto v = SpiralSequence();; ++v) {
        // AN improvement is to find a better way of choosing i,j this would greatly speed up the calculation
        for (unsigned int i = 0; i < m_hail.size() - 1; i++) {
            for (unsigned int j = i + 1; j < m_hail.size(); j++) {
                if (solveCollisions(i, j, v->first, v->second, pos)) {
                    return pos[0] + pos[1] + pos[2];
                }
            }
        }
    }
}

SpiralSequence &SpiralSequence::operator++() {
    if ((x == y) || ((x < 0) && (x == -y)) || ((x > 0) && (x == 1 - y))) {
        int t = dx;
        dx = -dy;
        dy = t;
    }
    x += dx;
    y += dy;
    ij = {x, y};
    return *this;
}
