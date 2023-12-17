#include <gtest/gtest.h>
#include "Day17.h"
#include "CrucibleMap.h"
// Demonstrate some basic assertions for new class.
TEST(Day17Test, Part1Part2) {
    std::stringstream in;
    in << "2413432311323\n";
    in << "3215453535623\n";
    in << "3255245654254\n";
    in << "3446585845452\n";
    in << "4546657867536\n";
    in << "1438598798454\n";
    in << "4457876987766\n";
    in << "3637877979653\n";
    in << "4654967986887\n";
    in << "4564679986453\n";
    in << "1224686865563\n";
    in << "2546548887735\n";
    in << "4322674655533\n";
    CrucibleMap cm(in);
    ASSERT_EQ(cm.getShortestPath(), 102);
}
