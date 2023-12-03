#include <gtest/gtest.h>
#include "GondolaManual.h"
// Demonstrate some basic assertions for new class.
TEST(Day03Test, Part1Part2) {
    std::stringstream in;
    in << "467..114..\n";
    in << "...*......\n";
    in << "..35..633.\n";
    in << "......#...\n";
    in << "617*......\n";
    in << ".....+.58.\n";
    in << "..592.....\n";
    in << "......755.\n";
    in << "...$.*....\n";
    in << ".664.598..\n";
    auto gm = GondolaManual(in);
    ASSERT_EQ(gm.getPartScore(), 4361);
    ASSERT_EQ(gm.getGearScore(), 467835);
    
}
