#include <gtest/gtest.h>
#include "Day07.h"
#include "CamelCards.h"
// Demonstrate some basic assertions for new class.
TEST(Day07Test, Part1Part2) {
    std::stringstream in;
    in << "32T3K 765\n";
    in << "T55J5 684\n";
    in << "KK677 28\n";
    in << "KTJJT 220\n";
    in << "QQQJA 483\n";
    CamelCards cc(in);
    ASSERT_EQ(cc.getScore(),6440);
    ASSERT_EQ(cc.getScoreJ(),5905);
}
