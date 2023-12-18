#include "TrenchPaint.h"
#include <regex>

TrenchPaint::TrenchPaint(std::istream &in) {
    std::regex rgx("(.) (\\d+) \\(#(.{5})(.)\\)");
    std::smatch matches;
    Coord cur = {0, 0};
    Coord cur2 = {0, 0};
    m_boundary_size = 0;
    m_boundary_size2 = 0;
    for(std::string x; std::getline(in, x);) {
        std::regex_search(x, matches, rgx);
        char dir = matches[1].str()[0];
        long int cnt = std::stol(matches[2].str());
        long int cnt2 = std::stol(matches[3].str(), nullptr, 16);
        char dir2 = matches[4].str()[0];
        m_boundary_size += cnt;
        m_boundary_size2 += cnt2;
        switch (dir) {
            case 'U' :
                cur.first -= cnt;
                break;
            case 'D' :
                cur.first += cnt;
                break;
            case 'L' :
                cur.second -= cnt;
                break;
            case 'R' :
                cur.second += cnt;
                break;
        }
        switch (dir2) {
            case '3' :
                cur2.first -= cnt2;
                break;
            case '1' :
                cur2.first += cnt2;
                break;
            case '2' :
                cur2.second -= cnt2;
                break;
            case '0' :
                cur2.second += cnt2;
                break;
        }
        m_corners.push_back(cur);
        m_corners2.push_back(cur2);
    }

}
unsigned long int calc(const std::vector<Coord> &corners, unsigned long int boundary_size) {
    // Use the shoelace formula to get the double area.
    long int darea = 0;
    for (unsigned int i = 0; i < (corners.size() - 1); i++) {
        darea += ((corners[i].first * corners[i + 1].second) - (corners[i + 1].first * corners[i].second));
    }
    darea += ((corners[(corners.size() - 1)].first * corners[0].second) - (corners[0].first * corners[(corners.size() - 1)].second));
    // Then pecks theorem to get the integer points contained
    return (std::abs(darea) / 2) + (boundary_size / 2) + 1;
}

unsigned long int TrenchPaint::getInterior() {
    return calc(m_corners, m_boundary_size);
}


unsigned long int TrenchPaint::getInterior2() {
    return calc(m_corners2, m_boundary_size2);
}