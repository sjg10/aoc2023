#pragma once
#include <string>
#include <set>
#include <vector>
#include <iostream>

using ulong=unsigned long int;

class MapRange {
public:
    MapRange(ulong out_start, ulong in_start, ulong length) :
    m_out_start(out_start), m_in_start(in_start), m_length(length) {};
    bool operator==(const MapRange& rhs) const {
        return (m_in_start == rhs.m_in_start);
    };
    bool operator<(const MapRange& rhs) const {
        return (m_in_start < rhs.m_in_start);
    };
//private:
    const ulong m_out_start;
    const ulong m_in_start;
    const ulong m_length;
};

class MapSet {
public:
    MapSet() {};
    void addRange(ulong out_start, ulong in_start, ulong length) {
        m_set.insert(MapRange(out_start, in_start, length));
    }
    ulong map(ulong val) const;
private:
    std::set<MapRange> m_set;
};

class SoilAlmanac {
public:
    SoilAlmanac(std::istream &input);
    ulong getLowestSeedLocation();
    ulong getLowestSeedLocationRanges();
private:
    std::vector<MapSet> m_maps;
    std::vector<ulong> m_seeds;
};