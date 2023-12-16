#include "BeamGrid.h"


BeamGrid::BeamGrid(std::istream &in) {
    for (std::string x; std::getline(in, x);) {
        m_map.push_back(std::vector<char>());
        for(auto const &c: x) {
            if (c != '\n') {m_map.back().push_back(c);}
        }
    }
}

// Updates history, returns new state without repeats
std::vector<State> update_history(const std::vector<State> &states, std::vector<std::vector<std::vector<bool>>> &history) {
    std::vector<State> ret;
    for(auto const &s : states) {
        if (!history[s.first.first][s.first.second][s.second]) {
            ret.push_back(s);
            history[s.first.first][s.first.second][s.second] = true;
        }
    }
    return ret;
}

State state(unsigned int r, unsigned int c, Direction d) {
    return std::make_pair(std::make_pair(r,c), d);
}

void move(State s, char tile, std::vector<State> &retstates, unsigned int rmax, unsigned int cmax) {
    unsigned int r = s.first.first;
    unsigned int c = s.first.second;
    Direction d = s.second;
    switch (tile) {
        case '.' :
            switch(d) {
                case NORTH: if (r != 0) {retstates.push_back(state(r - 1, c, d));}; break;
                case SOUTH: if (r != rmax) {retstates.push_back(state(r + 1, c, d));}; break;
                case EAST: if (c != cmax) {retstates.push_back(state(r, c + 1, d));}; break;
                case WEST: if (c != 0) {retstates.push_back(state(r, c - 1, d));}; break;
                default: throw std::runtime_error("Bad dir");
            }
            break;
        case '\\' :
            switch(d) {
                case NORTH: if (c != 0) {retstates.push_back(state(r, c - 1, WEST));}; break;
                case SOUTH: if (c != cmax) {retstates.push_back(state(r, c + 1, EAST));}; break;
                case EAST: if (r != rmax) {retstates.push_back(state(r + 1, c, SOUTH));}; break;
                case WEST: if (r != 0) {retstates.push_back(state(r - 1, c, NORTH));}; break;
                default: throw std::runtime_error("Bad dir");
            }
            break;
        case '/' :
            switch(d) {
                case NORTH: if (c != cmax) {retstates.push_back(state(r, c + 1, EAST));}; break;
                case SOUTH: if (c != 0) {retstates.push_back(state(r, c - 1, WEST));}; break;
                case EAST: if (r != 0) {retstates.push_back(state(r - 1, c, NORTH));}; break;
                case WEST: if (r != rmax) {retstates.push_back(state(r + 1, c, SOUTH));}; break;
                default: throw std::runtime_error("Bad dir");
            }
            break;
        case '|' :
            switch(d) {
                case NORTH: if (r != 0) {retstates.push_back(state(r - 1, c, d));}; break;
                case SOUTH: if (r != rmax) {retstates.push_back(state(r + 1, c, d));}; break;
                case EAST:
                case WEST: // fallthrough
                    if (r != 0) {retstates.push_back(state(r - 1, c, NORTH));};
                    if (r != rmax) {retstates.push_back(state(r + 1, c, SOUTH));};
                    break;
                default: throw std::runtime_error("Bad dir");
            }
            break;
        case '-' :
            switch(d) {
                case EAST: if (c != cmax) {retstates.push_back(state(r, c + 1, d));}; break;
                case WEST: if (c != 0) {retstates.push_back(state(r, c - 1, d));}; break;
                case NORTH:
                case SOUTH: // fallthrough
                    if (c != 0) {retstates.push_back(state(r, c - 1, WEST));};
                    if (c != cmax) {retstates.push_back(state(r, c + 1, EAST));};
                    break;
                default: throw std::runtime_error("Bad dir");
            }
            break;
        default: throw std::runtime_error("Bad char");
    }
}
unsigned int BeamGrid::walk() {
    return walk(state(0,0,EAST));
}


unsigned int BeamGrid::walk2() {
    unsigned int max = 0;
    unsigned int x = 0;
    unsigned int rmax = m_map.size() - 1;
    unsigned int cmax = m_map[0].size() - 1;
    for(unsigned int r = 0; r <= rmax; r++) {
        x = walk(state(r,0,EAST));
        if(x > max) { max = x;}

        x = walk(state(r,cmax,WEST));
        if(x > max) { max = x;}
    }

    for(unsigned int c = 0; c <= cmax; c++) {
        x = walk(state(0,c,SOUTH));
        if(x > max) { max = x;}
        x = walk(state(rmax,c,NORTH));
        if(x > max) { max = x;}
    }
    return max;
}

unsigned int BeamGrid::walk(State start) {
    unsigned int rmax = m_map.size() - 1;
    unsigned int cmax = m_map[0].size() - 1;
    std::vector<State> current = {start};
    std::vector<std::vector<std::vector<bool>>> history;
    for(unsigned int r = 0; r <= rmax; r++) {
        history.push_back(std::vector<std::vector<bool>>());
        for(unsigned int c = 0; c <= cmax; c++) {
            history[r].push_back(std::vector<bool>(4));//for each direction
         }
    }
    current = update_history(current, history);
    while (!current.empty()) {
        std::vector<State> newcurrent;
        for(auto const &s : current) {
            move(s, m_map[s.first.first][s.first.second], newcurrent, rmax, cmax);
        }
        current = update_history(newcurrent, history);
    }
    // Count lit squares
    unsigned int ret = 0;
    for(unsigned int r = 0; r < m_map.size(); r++) {
        history.push_back(std::vector<std::vector<bool>>());
        for(unsigned int c = 0; c < m_map.size(); c++) {
            if(std::find(history[r][c].begin(), history[r][c].end(), true) != history[r][c].end()) {
                ret++;
            }
        }
    }
    return ret;
}