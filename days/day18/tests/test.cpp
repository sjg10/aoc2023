#include <gtest/gtest.h>
#include "Day18.h"
#include "TrenchPaint.h"
// Demonstrate some basic assertions for new class.
TEST(Day18Test, Part1Part2) {
    std::stringstream in;
    in << "R 6 (#70c710)\n";
    in << "D 5 (#0dc571)\n";
    in << "L 2 (#5713f0)\n";
    in << "D 2 (#d2c081)\n";
    in << "R 2 (#59c680)\n";
    in << "D 2 (#411b91)\n";
    in << "L 5 (#8ceee2)\n";
    in << "U 2 (#caa173)\n";
    in << "L 1 (#1b58a2)\n";
    in << "U 2 (#caa171)\n";
    in << "R 2 (#7807d2)\n";
    in << "U 3 (#a77fa3)\n";
    in << "L 2 (#015232)\n";
    in << "U 2 (#7a21e3)\n";
    TrenchPaint tp(in);
    ASSERT_EQ(tp.getInterior(), 62);
}

