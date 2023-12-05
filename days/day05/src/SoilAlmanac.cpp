#include "SoilAlmanac.h"
#include <limits>
SoilAlmanac::SoilAlmanac(std::istream &input) {
    std::string x;
    std::getline(input, x);
    size_t offset = 7; // start reading first seed after title
    size_t nextoffset;
    do {
        nextoffset = x.find(" ", offset);
        if (nextoffset != std::string::npos) {
            nextoffset += 1;
            m_seeds.push_back(std::stoull(x.substr(offset, offset - nextoffset)));
        }
        else {
            m_seeds.push_back(std::stoull(x.substr(offset)));
            break;
        }
        offset = nextoffset;
    } while (true);

    bool end = false;
    std::getline(input, x); // skip gap

    while (!end) {
        std::getline(input, x); // skip title
        std::getline(input, x);
        m_maps.push_back(MapSet());
        while (x[0] >= '0' && x[0] <= '9') {
            offset = 0;
            nextoffset = x.find(" ", offset);
            nextoffset += 1;
            ulong out_start = std::stoull(x.substr(offset, offset - nextoffset));
            offset = nextoffset;
            nextoffset = x.find(" ", offset);
            nextoffset += 1;
            ulong in_start = std::stoull(x.substr(offset, offset - nextoffset));
            offset = nextoffset;
            ulong length = std::stoull(x.substr(offset));
            m_maps.back().addRange(out_start, in_start, length);
            if (!std::getline(input, x)) { 
                end = true;
                break;
            };
        }
    }
}

ulong MapSet::map(ulong val) const{
    for (auto const &itr : m_set) {
        if (val < itr.m_in_start) {
            break; // because ordered, will not be in a range
        }
        else if (val <= itr.m_in_start + (itr.m_length - 1)) {
            return itr.m_out_start + (val - itr.m_in_start);
        }
    }
    return val;
}


ulong SoilAlmanac::getLowestSeedLocation() {
    ulong min = std::numeric_limits<ulong>::max();
    for (auto const &seed: m_seeds) {
        auto val = seed;
        for (auto const &map: m_maps) {
            val = map.map(val);
        }
        if (val < min) {min = val;}
    }
    return min;
}

ulong SoilAlmanac::getLowestSeedLocationRanges() {
    ulong min = std::numeric_limits<ulong>::max();
    for (unsigned int i = 0; i < m_seeds.size(); i += 2) {
        for (ulong seed = m_seeds[i]; seed < m_seeds[i] + m_seeds[i + 1]; seed++) {
            // std::cout << "Test seed " << seed << std::endl;

            auto val = seed;
            for (auto const &map: m_maps) {
                val = map.map(val);
                // if (seed == 82) {
                //     std::cout << val <<std::endl;
                // }
            }
            if (val < min) {min = val;}
        }
    }
    return min;
}