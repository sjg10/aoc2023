#include <gtest/gtest.h>
#include "Scratchcards.h"
// Demonstrate some basic assertions for new class.
TEST(Day04Test, Part1Part2) {
    std::stringstream in;
    in << "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\n";
    in << "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19\n";
    in << "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1\n";
    in << "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83\n";
    in << "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36\n";
    in << "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11\n";
    auto sc = Scratchcards(in);
    auto ret = sc.getTotalScores();
    ASSERT_EQ(ret.first, 13);
    ASSERT_EQ(ret.second, 30);
}
