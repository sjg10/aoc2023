#include <gtest/gtest.h>
#include "PipeMap.h"
// Demonstrate some basic assertions for new class.
TEST(Day10Test, Part1A) {
    std::stringstream in;
    in << ".....\n";
    in << ".S-7.\n";
    in << ".|.|.\n";
    in << ".L-J.\n";
    in << ".....\n";
    PipeMap pm(in);
    ASSERT_EQ(pm.getBestDistance(), 4);
}

TEST(Day10Test, Part1B) {
    std::stringstream in;
    in << "..F7.\n";
    in << ".FJ|.\n";
    in << "SJ.L7\n";
    in << "|F--J\n";
    in << "LJ...\n";
    PipeMap pm(in);
    ASSERT_EQ(pm.getBestDistance(),8);
}
