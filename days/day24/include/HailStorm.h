#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <regex>

using Vector3D = std::array<long int, 3>;

class Hail {
public:
    Hail(const std::string &in);
    bool getCollision(const Hail &h, double &x, double &y) const;
    long int getPos(unsigned int i) const {return m_position[i];};
    long int getVel(unsigned int i) const {return m_velocity[i];};
private:
    static const std::regex rgx;
    Vector3D m_position;
    Vector3D m_velocity;
};


class HailStorm {
public:
    HailStorm(std::istream &in);
    long int getRock();
    unsigned int getCollisions(long int dmin, long int dmax);
private:
    bool solveCollisions(unsigned int i, unsigned int j, long int vx, long int vy, Vector3D &pos);
    std::vector<Hail> m_hail;
    std::vector<long int> t;
};


/** Iterator generating coordinates spiralling out from (0,0) */
class SpiralSequence : public std::iterator<std::input_iterator_tag, std::pair<int, int>> {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = std::pair<int, int>;
    using reference = value_type const &;
    using pointer = value_type const *;
    using difference_type = ptrdiff_t;

    SpiralSequence() {}
    explicit operator bool() const { return false; }
    reference operator*() const { return ij; }
    pointer operator->() const { return &ij; }
    SpiralSequence &operator++();
    SpiralSequence operator++(int) { SpiralSequence const tmp(*this); ++*this;  return tmp; }

private:
    value_type ij = {0, 0};
    int x = 0;
    int y = 0;
    int dx = 0;
    int dy = -1;
};