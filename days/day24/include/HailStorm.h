#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <regex>

using Vector3D = std::array<long int, 3>;
using Vector3DF = std::array<double, 3>;

class Hail {
public:
    Hail(const std::string &in);
    Vector3DF getCollision(const Hail &h) const;
private:
    static const std::regex rgx;
    Vector3D m_position;
    Vector3D m_velocity;
};


class HailStorm {
public:
    HailStorm(std::istream &in);
    unsigned int getCollisions(long int dmin, long int dmax);
private:
    std::vector<Hail> m_hail;
};