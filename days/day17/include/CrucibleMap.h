#pragma once
#include <iostream>
#include <vector>

using Coord = std::pair<unsigned int, unsigned int>;

enum Direction {
    INVALID,
    NORTH,
    EAST,
    WEST,
    SOUTH
};

//struct Pos {
//    unsigned int r = 0;
//    unsigned int c = 0;
//    Direction d = INVALID;
//    bool operator == (const Pos &rhs) const
//    { return r == rhs.r && c == rhs.c && d == rhs.d; }
//};


struct Pos {
    unsigned int r = 0;
    unsigned int c = 0;
    Direction d = INVALID;
    Direction d1 = INVALID;
    Direction d2 = INVALID;
    bool operator == (const Pos &rhs) const
    { return r == rhs.r && c == rhs.c && d == rhs.d && d1 == rhs.d1 && d2 == rhs.d2; }
};

template<class T>
class PosMap {
public:
    PosMap(unsigned int rmax, unsigned int cmax);
    T& operator [](const Pos &p);
private:
    unsigned int rmax;
    unsigned int cmax;
    std::vector<T> m_container;
};

class PosMapBool {
public:
    PosMapBool(unsigned int rmax, unsigned int cmax);
    std::vector<bool>::reference operator [](const Pos &p);
private:
    unsigned int rmax;
    unsigned int cmax;
    std::vector<bool> m_container;
};

class CrucibleMap {
public:
    CrucibleMap(std::istream &in);
    unsigned int getShortestPath();
private:
    std::vector<std::vector<unsigned int>> m_values;
    unsigned int rmax;
    unsigned int cmax;
};