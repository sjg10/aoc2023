#include <gtest/gtest.h>
#include "BeamGrid.h"
// Demonstrate some basic assertions for new class.
TEST(Day16Test, Part1Part2) {
    std::stringstream in;
    in << ".|...\\....\n";
    in << "|.-.\\.....\n";
    in << ".....|-...\n";
    in << "........|.\n";
    in << "..........\n";
    in << ".........\\\n";
    in << "..../.\\\\..\n";
    in << ".-.-/..|..\n";
    in << ".|....-|.\\\n";
    in << "..//.|....\n";
    BeamGrid bg(in);
    ASSERT_EQ(bg.walk(), 46);
    ASSERT_EQ(bg.walk2(), 51);
}

