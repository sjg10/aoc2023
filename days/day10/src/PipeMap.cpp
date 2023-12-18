#include "PipeMap.h"
#include <algorithm>


void rotcw(Direction &dir) {
    switch (dir) {
        case LEFT: dir= UP; break;
        case RIGHT: dir= DOWN; break;
        case UP: dir= RIGHT; break;
        case DOWN: dir= LEFT; break;
        default: throw std::runtime_error("Unknown dir"); break;
    }
}


void rotccw(Direction &dir) {
    switch (dir) {
        case LEFT: dir=DOWN; break;
        case RIGHT: dir= UP; break;
        case UP: dir= LEFT; break;
        case DOWN: dir= RIGHT; break;
        default: throw std::runtime_error("Unknown dir"); break;
    }
}


std::string dirstr(Direction dir) {
    switch (dir) {
        case LEFT: return "LEFT"; break;
        case RIGHT: return "RIGHT"; break;
        case UP: return "UP"; break;
        case DOWN: return "DOWN"; break;
        default: throw std::runtime_error("Unknown dir"); break;
    }
}

Coord move(const Coord &loc, Direction dir) {
    switch (dir) {
        case LEFT: return {loc.first, loc.second - 1}; break;
        case RIGHT: return {loc.first, loc.second + 1}; break;
        case UP: return {loc.first - 1, loc.second}; break;
        case DOWN: return {loc.first + 1, loc.second}; break;
        default: throw std::runtime_error("Unknown dir"); break;
    }
}

PipeMap::PipeMap(std::istream &in) {
    unsigned int row = 1;
    m_map.push_back(std::vector<std::vector<Coord>>());// initial added row
    for (std::string x; std::getline(in, x);) {
        m_map.push_back(std::vector<std::vector<Coord>>());
        m_map_char.push_back(std::vector<char>());
        m_map_char.back().push_back('O');
        m_map[row].push_back(std::vector<Coord>());
        for (unsigned int col = 1; col <= x.size(); col++) {
            m_map[row].push_back(std::vector<Coord>());
            m_map_char.back().push_back(x[col - 1]);
            switch (x[col - 1]) {
                case 'L': m_map[row][col]  = {move({row,col}, UP), move({row,col}, RIGHT)}; break;
                case '7': m_map[row][col]  = {move({row,col}, LEFT), move({row,col}, DOWN)}; break;
                case 'F': m_map[row][col]  = {move({row,col}, DOWN), move({row,col}, RIGHT)}; break;
                case 'J': m_map[row][col]  = {move({row,col}, LEFT), move({row,col}, UP)}; break;
                case '|': m_map[row][col]  = {move({row,col}, UP), move({row,col}, DOWN)}; break;
                case '-': m_map[row][col]  = {move({row,col}, LEFT), move({row,col}, RIGHT)}; break;
                case 'S': m_start = {row,col}; break;
                default: break;
            }
            m_map[row].push_back(std::vector<Coord>());
        }
        m_map_char.back().push_back('O');
        row++;
    }
    m_map.push_back(std::vector<std::vector<Coord>>());// initial added row
    m_map_char.insert(m_map_char.begin(), std::vector<char>(m_map_char[0].size(),'O'));
    m_map_char.push_back(std::vector<char>(m_map_char[0].size(), 'O'));
}

std::pair<unsigned int, unsigned int> PipeMap::getBestDistance() {
    auto next = move(m_start, DOWN);
    if (!m_map[next.first][next.second].empty()) {
        return getBestDistance(next);
    }
    next = move(m_start, UP);
    if (!m_map[next.first][next.second].empty()) {
        return getBestDistance(next);
    }
    next = move(m_start, RIGHT);
    if (!m_map[next.first][next.second].empty()) {
        return getBestDistance(next);
    }
    throw std::runtime_error("S has no neighbours!");
}

bool isCorner(char tile) {
    return (tile == 'L' || tile == '7' || tile == 'J' || tile == 'F');
}

std::pair<unsigned int, unsigned int> PipeMap::getBestDistance(Coord start2) {
    Coord cur = start2;
    Coord last = m_start;
    std::vector<Coord> corners;
    unsigned int distance = 1;
    if(isCorner(m_map_char[cur.first][cur.second])) {
        corners.push_back(cur);
    };
    while (cur != m_start) {
        // Move
        for (auto const &l: m_map[cur.first][cur.second]) {
            //calc next on path
            if (l != last) {
                last = cur;
                cur = l;
                distance++;
                break;
            }
        }
        if(isCorner(m_map_char[cur.first][cur.second])) {
            corners.push_back(cur);
        };
    }
    corners.push_back(m_start); // the start may or may not be a corner, it works either way

    // Use the shoelace formula to get the double area.
    long int darea = 0;
    for (unsigned int i = 0; i < (corners.size() - 1); i++) {
        darea += (long int)((corners[i].first * corners[i + 1].second) - (long int)(corners[i + 1].first * corners[i].second));
    }
    darea += (long int)((corners[(corners.size() - 1)].first * corners[0].second) - (long int)(corners[0].first * corners[(corners.size() - 1)].second));
    // Then picks theorem to get the integer points contained
    unsigned long int r2 =  ((std::abs(darea) / 2) - (distance / 2)) + 1;

    return {distance / 2,  r2};
}