#include <gtest/gtest.h>
#include "Day21.h"
#include "GardenPath.h"
// Demonstrate some basic assertions for new class.
TEST(Day21Test, Part1Part2) {
    std::stringstream in;
    in << "...........\n";
    in << ".....###.#.\n";
    in << ".###.##..#.\n";
    in << "..#.#...#..\n";
    in << "....#.#....\n";
    in << ".##..S####.\n";
    in << ".##..#...#.\n";
    in << ".......##..\n";
    in << ".##.#.####.\n";
    in << ".##..##.##.\n";
    in << "...........\n";
    GardenPath gp(in);
    ASSERT_EQ(gp.getReachable(6), 16);
}










































