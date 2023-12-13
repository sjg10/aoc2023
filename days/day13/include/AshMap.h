#pragma once
#include <iostream>
#include <vector>

class AshMap {
public:
    AshMap(std::istream &in);
    std::pair<unsigned int, unsigned int> getReflectiveIndex() const;
private:
    std::vector<unsigned int> m_rows;
    std::vector<unsigned int> m_cols;
};

class AshMaps {
public:
    AshMaps(std::istream &in);
    std::pair<unsigned int, unsigned int> getReflectiveIndexTotal();
private:
    std::vector<AshMap> m_maps;
};