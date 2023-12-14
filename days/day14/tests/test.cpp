#include <gtest/gtest.h>
#include "RockRoll.h"
// Demonstrate some basic assertions for new class.
TEST(Day14Test, Part1Part2) {
    std::stringstream in;
    in << "O....#....\n";
    in << "O.OO#....#\n";
    in << ".....##...\n";
    in << "OO.#O....O\n";
    in << ".O.....O#.\n";
    in << "O.#..O.#.#\n";
    in << "..O..#O..O\n";
    in << ".......O..\n";
    in << "#....###..\n";
    in << "#OO..#....\n";
    RockRoll rr(in);
    ASSERT_EQ(rr.getRollScore(), 136);
    ASSERT_EQ(rr.getRollScore2(), 64);
}









