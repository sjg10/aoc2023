#include <gtest/gtest.h>
#include "SoilAlmanac.h"
// Demonstrate some basic assertions for new class.
TEST(Day05Test, Part1Part2) {
    std::stringstream in;
    in << "seeds: 79 14 55 13\n";
    in << "\n";
    in << "seed-to-soil map:\n";
    in << "50 98 2\n";
    in << "52 50 48\n";
    in << "\n";
    in << "soil-to-fertilizer map:\n";
    in << "0 15 37\n";
    in << "37 52 2\n";
    in << "39 0 15\n";
    in << "\n";
    in << "fertilizer-to-water map:\n";
    in << "49 53 8\n";
    in << "0 11 42\n";
    in << "42 0 7\n";
    in << "57 7 4\n";
    in << "\n";
    in << "water-to-light map:\n";
    in << "88 18 7\n";
    in << "18 25 70\n";
    in << "\n";
    in << "light-to-temperature map:\n";
    in << "45 77 23\n";
    in << "81 45 19\n";
    in << "68 64 13\n";
    in << "\n";
    in << "temperature-to-humidity map:\n";
    in << "0 69 1\n";
    in << "1 0 69\n";
    in << "\n";
    in << "humidity-to-location map:\n";
    in << "60 56 37\n";
    in << "56 93 4\n";
    auto sa = SoilAlmanac(in);
    ASSERT_EQ(sa.getLowestSeedLocation(),35);
    ASSERT_EQ(sa.getLowestSeedLocationRanges(),46);
}
