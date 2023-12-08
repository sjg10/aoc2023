#include <gtest/gtest.h>
#include "Day08.h"
#include "DesertMap.h"
// Demonstrate some basic assertions for new class.
TEST(Day08Test, A) {
    std::stringstream in;
    in << "RL\n";
    in << "\n";
    in << "AAA = (BBB, CCC)\n";
    in << "BBB = (DDD, EEE)\n";
    in << "CCC = (ZZZ, GGG)\n";
    in << "DDD = (DDD, DDD)\n";
    in << "EEE = (EEE, EEE)\n";
    in << "GGG = (GGG, GGG)\n";
    in << "ZZZ = (ZZZ, ZZZ)\n";
    DesertMap dm(in);
    ASSERT_EQ(dm.navigate(),2);
}

TEST(Day08Test, B) {
    std::stringstream in;
    in << "LLR\n";
    in << "\n";
    in << "AAA = (BBB, BBB)\n";
    in << "BBB = (AAA, ZZZ)\n";
    in << "ZZZ = (ZZZ, ZZZ)\n";
    DesertMap dm(in);
    ASSERT_EQ(dm.navigate(),6);
}

TEST(Day08Test, C) {
    std::stringstream in;
    in << "LR\n";
    in << "\n";
    in << "11A = (11B, XXX)\n";
    in << "11B = (XXX, 11Z)\n";
    in << "11Z = (11B, XXX)\n";
    in << "22A = (22B, XXX)\n";
    in << "22B = (22C, 22C)\n";
    in << "22C = (22Z, 22Z)\n";
    in << "22Z = (22B, 22B)\n";
    in << "XXX = (XXX, XXX)\n";
    DesertMap dm(in);
    ASSERT_EQ(dm.navigateGhosts(),6);
}
