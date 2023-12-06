#include <gtest/gtest.h>
#include "Day06.h"
#include "Day06.h"
// Demonstrate some basic assertions for new class.
TEST(Day06Test, Part1Part2) {
    std::stringstream in;
    in << "Time:      7  15   30\n";
    in << "Distance:  9  40  200\n";

    std::vector<std::pair<unsigned int, unsigned int>> races = Day06::parseScores(in);
    auto ret = Day06::getScore(races);
    ASSERT_EQ(ret.first, 288);
    ASSERT_EQ(ret.second, 71503);
}
