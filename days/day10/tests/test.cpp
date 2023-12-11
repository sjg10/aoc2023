#include <gtest/gtest.h>
#include "PipeMap.h"
// Demonstrate some basic assertions for new class.
TEST(Day10Test, Part1A) {
    std::stringstream in;
    in << ".....\n";
    in << ".S-7.\n";
    in << ".|.|.\n";
    in << ".L-J.\n";
    in << ".....\n";
    PipeMap pm(in);
    ASSERT_EQ(pm.getBestDistance().first, 4);
}

TEST(Day10Test, Part1B) {
    std::stringstream in;
    in << "..F7.\n";
    in << ".FJ|.\n";
    in << "SJ.L7\n";
    in << "|F--J\n";
    in << "LJ...\n";
    PipeMap pm(in);
    ASSERT_EQ(pm.getBestDistance().first,8);
}

TEST(Day10Test, Part2A) {
    std::stringstream in;
    in << "...........\n";
    in << ".S-------7.\n";
    in << ".|F-----7|.\n";
    in << ".||.....||.\n";
    in << ".||.....||.\n";
    in << ".|L-7.F-J|.\n";
    in << ".|..|.|..|.\n";
    in << ".L--J.L--J.\n";
    in << "...........\n";
    PipeMap pm(in);
    ASSERT_EQ(pm.getBestDistance().second,4);
}

TEST(Day10Test, Part2AMod) {
    std::stringstream in;
    in << "..........\n";
    in << ".S------7.\n";
    in << ".|F----7|.\n";
    in << ".||....||.\n";
    in << ".||....||.\n";
    in << ".|L-7F-J|.\n";
    in << ".|..||..|.\n";
    in << ".L--JL--J.\n";
    in << "..........\n";
    PipeMap pm(in);
    ASSERT_EQ(pm.getBestDistance().second,4);
}

TEST(Day10Test, Part2B) {
    std::stringstream in;
    in << ".F----7F7F7F7F-7....\n";
    in << ".|F--7||||||||FJ....\n";
    in << ".||.FJ||||||||L7....\n";
    in << "FJL7L7LJLJ||LJ.L-7..\n";
    in << "L--J.L7...LJS7F-7L7.\n";
    in << "....F-J..F7FJ|L7L7L7\n";
    in << "....L7.F7||L7|.L7L7|\n";
    in << ".....|FJLJ|FJ|F7|.LJ\n";
    in << "....FJL-7.||.||||...\n";
    in << "....L---J.LJ.LJLJ...\n";
    PipeMap pm(in);
    ASSERT_EQ(pm.getBestDistance().second,8);
}
TEST(Day10Test, Part2C) {
    std::stringstream in;
    in << "FF7FSF7F7F7F7F7F---7\n";
    in << "L|LJ||||||||||||F--J\n";
    in << "FL-7LJLJ||||||LJL-77\n";
    in << "F--JF--7||LJLJ7F7FJ-\n";
    in << "L---JF-JLJ.||-FJLJJ7\n";
    in << "|F|F-JF---7F7-L7L|7|\n";
    in << "|FFJF7L7F-JF7|JL---7\n";
    in << "7-L-JL7||F7|L7F-7F7|\n";
    in << "L.L7LFJ|||||FJL7||LJ\n";
    in << "L7JLJL-JLJLJL--JLJ.L\n";
    PipeMap pm(in);
    ASSERT_EQ(pm.getBestDistance().second,10);
}