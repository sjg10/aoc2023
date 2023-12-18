#include "TrenchPaint.h"
#include <regex>

TrenchPaint::TrenchPaint(std::istream &in) {
    std::regex rgx("(.) (\\d+) \\(#(.{6})\\)");
    std::smatch matches;
    Coord cur = {0, 0};
    Tile prevdir = NONE;
    for(std::string x; std::getline(in, x);) {
        std::regex_search(x, matches, rgx);
        std::cout << matches[1].str() << ":" << matches[2].str() << ":" << matches[3].str() << ":" << std::endl;
        char dir = matches[1].str()[0];
        int cnt = std::stol(matches[2].str());
        uint32_t clr = std::stoul(matches[3].str(), nullptr, 16);
        switch (dir) {
            case 'U' :
                for(int i = 0; i < cnt; i++) {
                    m_map[{cur.first - i, cur.second}] = {UP, prevdir, clr};
                    prevdir = UP;
                }
                cur.first -= cnt;
                if (cur.first < xmin) {xmin = cur.first;}
                break;
            case 'D' :
                for(int i = 0; i < cnt; i++) {
                    m_map[{cur.first + i, cur.second}] = {DOWN, prevdir, clr};
                    prevdir = DOWN;
                }
                cur.first += cnt;
                if (cur.first > xmax) {xmax = cur.first;}
                break;
            case 'L' :
                for(int i = 0; i < cnt; i++) {
                    m_map[{cur.first, cur.second - i}] = {LEFT, prevdir, clr};
                    prevdir = LEFT;
                }
                cur.second -= cnt;
                if (cur.second < ymin) {ymin = cur.second;}
                break;
            case 'R' :
                for(int i = 0; i < cnt; i++) {
                    m_map[{cur.first, cur.second + i}] = {RIGHT, prevdir, clr};
                    prevdir = RIGHT;
                }
                cur.second += cnt;
                if (cur.second > ymax) {ymax = cur.second;}
                break;
        }
    }
    std::get<1>(m_map[{0, 0}]) = prevdir;
    for(cur.first = xmin ; cur.first <= xmax; cur.first++) {
        for (cur.second = ymin; cur.second <= ymax; cur.second++) {
            if(m_map.contains(cur)) {
                std::cout << '#';
            }
            else {
                std::cout << '.';
            }
        }
        std::cout <<std::endl;
    }
    std::cout <<std::endl;
}

unsigned int TrenchPaint::getInterior() {
    unsigned int cnt = 0;
    Coord pos = {xmin, ymin};

    for(pos.first = xmin; pos.first <= xmax; pos.first++) {
        Tile tile = NONE;
        Tile ptile = NONE;
        Tile lasttile = NONE;
        Tile lastptile = NONE;
        Tile runfirsttile = NONE;
        Tile runfirstptile = NONE;
        bool inside = false;
        bool lastinside = false;
        for (pos.second = ymin; pos.second <= ymax; pos.second++) {
            lasttile = tile;
            lastptile = ptile;
            try {
                auto m = m_map.at(pos);
                tile = std::get<0>(m);
                ptile = std::get<1>(m);
            } catch (std::out_of_range &e) {
                tile = NONE;
                ptile = NONE;
            }

            //starting a run
            if (lasttile == NONE && tile != NONE) {
                // save some info
                lastinside = inside;
                runfirsttile = tile;
                runfirstptile = ptile;

                // update
                inside = true;
            }
            //just ended a run
            else if (tile == NONE && lasttile != NONE) {
                if((lasttile == UP && runfirsttile == UP) || (lasttile == DOWN && runfirsttile == DOWN)) {
                    //just crossed a simple up or down
                    inside = !lastinside;
                }
                else if ((runfirsttile == RIGHT)  && (runfirstptile == lasttile)){ // right headed switch
                    inside = !lastinside;
                }
                else if ((lasttile == LEFT)  && (runfirsttile == lastptile)){ // left headed switch
                    inside = !lastinside;
                }
                else if (runfirsttile == RIGHT && (runfirstptile != lasttile)) { // right headed U
                    inside = lastinside;
                }
                else if ((lasttile == LEFT)  && (runfirsttile != lastptile)) { // left headed U
                    inside = lastinside;
                }

            }
            //otherwise nothing changes
            if (inside) {
                std::cout << '#';
                cnt++;
            } else {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    return cnt;
}
