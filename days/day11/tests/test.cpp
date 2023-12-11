#include <gtest/gtest.h>
#include "Day11.h"
#include "SkyMap.h"
// Demonstrate some basic assertions for new class.
TEST(Day11Test, Part1Part2) {
    std::stringstream in;
    in << "...#......\n";
    in << ".......#..\n";
    in << "#.........\n";
    in << "..........\n";
    in << "......#...\n";
    in << ".#........\n";
    in << ".........#\n";
    in << "..........\n";
    in << ".......#..\n";
    in << "#...#.....\n";
    SkyMap sm(in);
    ASSERT_EQ(sm.getShortestSum(), 374);
    ASSERT_EQ(sm.getShortestSum(10), 1030);
    ASSERT_EQ(sm.getShortestSum(100), 8410);
}
