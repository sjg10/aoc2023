#include <gtest/gtest.h>
#include "AshMap.h"
// Demonstrate some basic assertions for new class.
TEST(Day13Test, Part1Part2) {
    std::stringstream in;
    in << "#.##..##.\n";
    in << "..#.##.#.\n";
    in << "##......#\n";
    in << "##......#\n";
    in << "..#.##.#.\n";
    in << "..##..##.\n";
    in << "#.#.##.#.\n";
    in << "\n";
    in << "#...##..#\n";
    in << "#....#..#\n";
    in << "..##..###\n";
    in << "#####.##.\n";
    in << "#####.##.\n";
    in << "..##..###\n";
    in << "#....#..#\n";
    AshMaps am(in);
    auto ret = am.getReflectiveIndexTotal();
    ASSERT_EQ(ret.first, 405);
    ASSERT_EQ(ret.second, 400);
}
