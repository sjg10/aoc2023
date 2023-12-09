#include <gtest/gtest.h>
#include "Day09.h"
#include "OASIS.h"
// Demonstrate some basic assertions for new class.
TEST(Day09Test, Part1Part2) {
    std::stringstream in;
    in << "0 3 6 9 12 15\n";
    in << "1 3 6 10 15 21\n";
    in << "10 13 16 21 30 45\n";
    OASIS oa(in);
    ASSERT_EQ(oa.getNextTermSumScore(), 114);
    ASSERT_EQ(oa.getPrevTermSumScore(), 2);
}
