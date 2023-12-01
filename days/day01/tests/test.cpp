#include <gtest/gtest.h>
#include "Day01.h"
// Demonstrate some basic assertions for new class.
TEST(Day01Test, Part1) {
    std::stringstream in;
    in << "1abc2\n";
    in << "pqr3stu8vwx\n";
    in << "a1b2c3d4e5f\n";
    in << "treb7uchet\n";
    auto ret = Day01::getCalibrationSum(in);
    ASSERT_EQ(ret.first, 142);
}

TEST(Day01Test, Part2) {
    std::stringstream in;
    in << "two1nine\n";
    in << "eightwothree\n";
    in << "abcone2threexyz\n";
    in << "xtwone3four\n";
    in << "4nineeightseven2\n";
    in << "zoneight234\n";
    in << "7pqrstsixteen\n";
    auto ret = Day01::getCalibrationSum(in);
    ASSERT_EQ(ret.second, 281);
}