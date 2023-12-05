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

std::vector<std::pair<ulong, ulong>> MapSet::map(std::vector<std::pair<ulong, ulong>> input_ranges) const {
    std::vector<std::pair<ulong, ulong>> out;
    std::vector<std::pair<ulong, ulong>> further_input_ranges;
    do {
        further_input_ranges = std::vector<std::pair<ulong, ulong>>();
        for (auto const &range: input_ranges) {
            ulong start_val = range.first;
            ulong start_val_mapped = 0;
            bool mapped = false;
            ulong count = std::numeric_limits<ulong>::max();
            std::set<MapRange>::iterator itr;
            for (itr = m_set.begin(); itr != m_set.end(); ++itr) {
                if (start_val < itr->m_in_start) {// because ordered, we know this wont end up mapped!
                    start_val_mapped = start_val;
                    mapped = true;
                    count = itr->m_in_start - start_val;
                }
                else if (start_val <= itr->m_in_start + (itr->m_length - 1)) {
                    start_val_mapped = itr->m_out_start + (start_val - itr->m_in_start);
                    count = itr->m_length - (start_val - itr->m_in_start);
                    mapped = true;
                }
                if(mapped) { break; }
            }
            if (!mapped) {
                start_val_mapped = start_val;
                count = std::numeric_limits<ulong>::max();
            }
            if (count >= range.second) { // mapped everything!
                out.push_back({start_val_mapped, range.second});
            }
            else { //mapped_partial
                out.push_back({start_val_mapped, count});
                further_input_ranges.push_back({start_val + count, range.second - count});
            }
        }
        input_ranges = further_input_ranges;
    } while (!further_input_ranges.empty());
    return out;
}



ulong SoilAlmanac::getLowestSeedLocation() {
    ulong min = std::numeric_limits<ulong>::max();
    for (auto const &seed: m_seeds) {
        std::vector<std::pair<ulong, ulong>> val_ranges = {{seed, 1}};
        for (auto const &map: m_maps) {
            val_ranges = map.map(val_ranges);
        }
        for (auto const &r: val_ranges) {
            if (r.first < min) {min = r.first;}
        }
    }
    return min;
}

ulong SoilAlmanac::getLowestSeedLocationRanges() {
    ulong min = std::numeric_limits<ulong>::max();
    for (unsigned int i = 0; i < m_seeds.size(); i += 2) {
        std::vector<std::pair<ulong, ulong>> val_ranges = {{m_seeds[i], m_seeds[i + 1]}};
        for (auto const &map: m_maps) {
            val_ranges = map.map(val_ranges);
        }
        for (auto const &r: val_ranges) {
            if (r.first < min) {min = r.first;}
        }
    }
    return min;
}