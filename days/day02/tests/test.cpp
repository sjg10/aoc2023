#include <gtest/gtest.h>
#include "Day02.h"
#include "CubeGame.h"
// Demonstrate some basic assertions for new class.
TEST(Day02Test, Part1Part2) {
    std::stringstream in;
    in << "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n";
    in << "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n";
    in << "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\n";
    in << "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\n";
    in << "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green\n";
    unsigned int sum = 0;
    unsigned int psum = 0;
    for(std::string x; std::getline(in, x);) {
        auto cg = CubeGame(x);
        sum += cg.comptaibleScore(12,13,14);
        psum += cg.powerScore();
    }
    ASSERT_EQ(sum, 8);
    ASSERT_EQ(psum, 2286);
}
