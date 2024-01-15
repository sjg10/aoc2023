#include <gtest/gtest.h>
#include "Day24.h"
#include "HailStorm.h"

// Demonstrate some basic assertions for new class.
TEST(Day24Test, Part1Part2) {
    std::stringstream in;
    in << "19, 13, 30 @ -2,  1, -2\n";
    in << "18, 19, 22 @ -1, -1, -2\n";
    in << "20, 25, 34 @ -2, -2, -4\n";
    in << "12, 31, 28 @ -1, -2, -1\n";
    in << "20, 19, 15 @  1, -5, -3\n";
    HailStorm hs(in);
    ASSERT_EQ(hs.getCollisions(7, 27), 2);
    ASSERT_EQ(hs.getRock(), 47);
}
