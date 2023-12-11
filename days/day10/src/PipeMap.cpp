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
        return getBestDistance(next, DOWN);
    }
    next = move(m_start, UP);
    if (!m_map[next.first][next.second].empty()) {
        return getBestDistance(next, UP);
    }
    next = move(m_start, RIGHT);
    if (!m_map[next.first][next.second].empty()) {
        return getBestDistance(next, RIGHT);
    }
    throw std::runtime_error("S has no neighbours!");
}

bool rotateOnCorner(Direction &inside_dir, Direction &outside_dir, char tile, Coord last, Coord cur) {
    switch(tile) {
        case 'L':
            if (move(last, DOWN) == cur) {
                rotccw(inside_dir);
                rotccw(outside_dir);
            }
            else  {
                rotcw(inside_dir);
                rotcw(outside_dir);
            }
            return true;
            break;
        case '7':
            if (move(last, UP) == cur) {
                rotccw(inside_dir);
                rotccw(outside_dir);
            }
            else  {
                rotcw(inside_dir);
                rotcw(outside_dir);
            }
            return true;
            break;
        case 'F':
            if (move(last, LEFT) == cur)  {
                rotccw(inside_dir);
                rotccw(outside_dir);
            }
            else  {
                rotcw(inside_dir);
                rotcw(outside_dir);
            }
            return true;
            break;
        case 'J':
            if (move(last, RIGHT) == cur)  {
                rotccw(inside_dir);
                rotccw(outside_dir);
            }
            else  {
                rotcw(inside_dir);
                rotcw(outside_dir);
            }
            return true;
            break;
        default:
            return false;
            break;
    }
    return false;
}

std::pair<unsigned int, unsigned int> PipeMap::getBestDistance(Coord start2, Direction moved) {
    Coord cur = start2;
    Coord last = m_start;
    Direction inside_dir = moved; rotcw(inside_dir);
    Direction outside_dir = moved; rotccw(outside_dir);
    std::set<Coord> inside_region = {move(start2, inside_dir)};
    std::set<Coord> outside_region = {move(start2, outside_dir)};
    std::set<Coord> path = {m_start, start2};
    unsigned int distance = 1;
    // initial rotate if start2 on corner
    if(rotateOnCorner(inside_dir, outside_dir, m_map_char[cur.first][cur.second], last, cur)) {
        inside_region.insert(move(cur, inside_dir));
        outside_region.insert(move(cur, outside_dir));
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
        // add neighbours to regions before turn after move
        inside_region.insert(move(cur, inside_dir));
        outside_region.insert(move(cur, outside_dir));
        //check if we turn and update "side" directions
        if(rotateOnCorner(inside_dir, outside_dir, m_map_char[cur.first][cur.second], last, cur)) {
            //after a possible rotating, add border regions again
            inside_region.insert(move(cur, inside_dir));
            outside_region.insert(move(cur, outside_dir));
        };
        path.insert(cur);
    }

    // flood regions
    bool inside = floodRegions(inside_region, path);
    bool inside2 = floodRegions(outside_region, path);
    if (inside == inside2) { throw std::runtime_error("Two outsides?");}
    if (!inside) {inside_region.swap(outside_region);}
    return {distance / 2,  inside_region.size()};
}

/** Flood out a collection of regions, bounded by the path and the edge of the map.
 * Return true iff no part of the region touches the map edge */
bool PipeMap::floodRegions(std::set<Coord> &region, const std::set<Coord> & path) {
    bool inside = true;
    // Remove the path
    std::set<Coord> c;
    std::set_difference(region.begin(), region.end(), path.begin(), path.end(), std::inserter(c, c.begin()));
    region.swap(c);

    // Start adding neighbours
    std::set<Coord> additional = region;
    while(!additional.empty()) {
        region.insert(additional.begin(), additional.end());
        std::set<Coord> recent;
        recent.swap(additional);
        for(auto const &l : recent) { // for each recently added member
            // if in border don't find neighbours to prevent overrun
            if (m_map_char[l.first][l.second] == 'O') {
                inside = false;
                continue;
            }
            std::vector<Direction> dirs = {UP, DOWN, LEFT, RIGHT};
            // get new neighbours not in path
            for (auto const &dir: dirs) {
                auto l2 = move(l, dir);
                if (!path.contains(l2) & !region.contains(l2)) {
                    additional.insert(l2);
                }
            }
        }
    }
    return inside;
}