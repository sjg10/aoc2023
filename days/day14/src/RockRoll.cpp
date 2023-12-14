#include "RockRoll.h"

RockRoll::RockRoll(std::istream &in) {
    unsigned int row = 0;
    for (std::string x; std::getline(in, x);) {
        for (unsigned int col = 0; col < x.size(); col++) {
            if (row == 0) { m_rocks.push_back(std::vector<Tile>()); }
            switch(x[col]) {
                case 'O': m_rocks[col].push_back(ROUND);break;
                case '.': m_rocks[col].push_back(EMPTY);break;
                case '#': m_rocks[col].push_back(CUBE);break;
            }
        }
        row++;
    }
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<Tile>> &m) {
    for (unsigned int row = 0; row < m[0].size(); row++) {
        for (unsigned int col = 0; col < m.size(); col++) {
            switch (m[col][row]) {
                case ROUND:
                    os << 'O';
                    break;
                case CUBE:
                    os << '#';
                    break;
                case EMPTY:
                    os << '.';
                    break;
            }
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}

unsigned int calc(const std::vector<std::vector<Tile>> &rocks) {
    unsigned int ret = 0;
    for (unsigned int col = 0; col < rocks.size(); col++) {
        for (unsigned int row = 0; row < rocks[col].size(); row++) {
            if (rocks[col][row] == ROUND) {
                ret += rocks[col].size() - row;
            }
        }
    }
    return ret;
}

void slide_north(std::vector<std::vector<Tile>> &rocks) {
    for (unsigned int col = 0; col < rocks.size(); col++) {
        unsigned int settle_point = 0;
        for (unsigned int row = 0; row < rocks[col].size(); row++) {
            switch (rocks[col][row]) {
                case ROUND:
                    rocks[col][row] = EMPTY;
                    rocks[col][settle_point] = ROUND;
                    settle_point = settle_point + 1;
                    break;
                case CUBE:
                    settle_point = row + 1;
                    break;
                default:
                    break;
            }
        }
    }
}

void slide_west(std::vector<std::vector<Tile>> &rocks) {
    for (unsigned int row = 0; row < rocks[0].size(); row++) {
        unsigned int settle_point = 0;
        for (unsigned int col = 0; col < rocks.size(); col++) {
            switch (rocks[col][row]) {
                case ROUND:
                    rocks[col][row] = EMPTY;
                    rocks[settle_point][row] = ROUND;
                    settle_point = settle_point + 1;
                    break;
                case CUBE:
                    settle_point = col + 1;
                    break;
                default:
                    break;
            }
        }
    }
}

void slide_south(std::vector<std::vector<Tile>> &rocks) {
    for (unsigned int col = 0; col < rocks.size(); col++) {
        unsigned int settle_point = rocks.size() - 1;
        for (int row = (int) rocks[col].size() - 1; row >= 0; row--) {
            switch (rocks[col][row]) {
                case ROUND:
                    rocks[col][row] = EMPTY;
                    rocks[col][settle_point] = ROUND;
                    settle_point = settle_point - 1;
                    break;
                case CUBE:
                    settle_point = row - 1;
                    break;
                default:
                    break;
            }
        }
    }
}

void slide_east(std::vector<std::vector<Tile>> &rocks) {
    for (unsigned int row = 0; row < rocks[0].size(); row++) {
        unsigned int settle_point = rocks[0].size() - 1;
        for (int col = (int) rocks.size() - 1; col >= 0; col--) {
            switch (rocks[col][row]) {
                case ROUND:
                    rocks[col][row] = EMPTY;
                    rocks[settle_point][row] = ROUND;
                    settle_point = settle_point - 1;
                    break;
                case CUBE:
                    settle_point = col - 1;
                    break;
                default:
                    break;
            }
        }
    }
}

unsigned int RockRoll::getRollScore() {
    auto rocks = m_rocks;
    slide_north(rocks);
    return calc(rocks);
}

unsigned int RockRoll::getRollScore2() {
    auto rocks = m_rocks;
    std::vector<std::vector<std::vector<Tile>>> seen_rocks = {rocks};
    for (unsigned int i = 0; i <1000000000; i++) {
        slide_north(rocks);
        slide_west(rocks);
        slide_south(rocks);
        slide_east(rocks);
        auto itr = std::find(seen_rocks.begin(), seen_rocks.end(), rocks);
        if(itr != seen_rocks.end()) {
            //Done!
            unsigned int done_cycles = i + 1;
            unsigned int rep = itr - seen_rocks.begin();
            unsigned int period = (done_cycles - rep); // pattern repeats with given period
            unsigned int desired = (((1000000000 - rep) % period) + rep);
            rocks = seen_rocks[desired];
            break;
        }
        else {
            seen_rocks.push_back(rocks);
        }
    }
    return calc(rocks);
}
