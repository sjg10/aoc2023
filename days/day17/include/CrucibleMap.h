#pragma once
#include <iostream>
#include <vector>

const int MAX_POSSIBLE_RUN_LENGTH = 10; // questions dont want nay more than that!
using Coord = std::pair<unsigned int, unsigned int>;

enum Direction {
    INVALID,
    NORTH,
    EAST,
    WEST,
    SOUTH
};

struct Pos {
    unsigned int r = 0;
    unsigned int c = 0;
    Direction d = INVALID;
    unsigned int cur_run_length = 0;
    bool operator == (const Pos &rhs) const
    { return r == rhs.r && c == rhs.c && d == rhs.d && cur_run_length==rhs.cur_run_length;}
};

template<class T>
class PosMap {
public:
    PosMap(unsigned int rmax, unsigned int cmax);
    template<class Q=T>
    typename std::enable_if <!std::is_same<Q,bool>::value, Q&>::type  operator [](const Pos &p);
    template<class Q=T>
    typename std::enable_if <std::is_same<Q,bool>::value, std::vector<bool>::reference>::type operator [](const Pos &p);
private:
    unsigned int getOffset(const Pos &p);
    unsigned int rmax;
    unsigned int cmax;
    std::vector<T> m_container;
};

/*
class PosMapBool {
public:
    PosMapBool(unsigned int rmax, unsigned int cmax);
    std::vector<bool>::reference operator[](const Pos &p);
private:
    unsigned int rmax;
    unsigned int cmax;
    std::vector<bool> m_container;
};
*/

class CrucibleMap {
public:
    CrucibleMap(std::istream &in);
    unsigned int getShortestPath(unsigned int minrun = 0, unsigned int maxrun = 3);
private:
    std::vector<std::vector<unsigned int>> m_values;
    unsigned int rmax;
    unsigned int cmax;
};