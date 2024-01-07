#include <gtest/gtest.h>
#include "Day23.h"
#include "ForestWalk.h"
// Demonstrate some basic assertions for new class.
TEST(Day23Test, Part1Part2) {
    std::stringstream in;
    in << "#.#####################\n";
    in << "#.......#########...###\n";
    in << "#######.#########.#.###\n";
    in << "###.....#.>.>.###.#.###\n";
    in << "###v#####.#v#.###.#.###\n";
    in << "###.>...#.#.#.....#...#\n";
    in << "###v###.#.#.#########.#\n";
    in << "###...#.#.#.......#...#\n";
    in << "#####.#.#.#######.#.###\n";
    in << "#.....#.#.#.......#...#\n";
    in << "#.#####.#.#.#########v#\n";
    in << "#.#...#...#...###...>.#\n";
    in << "#.#.#v#######v###.###v#\n";
    in << "#...#.>.#...>.>.#.###.#\n";
    in << "#####v#.#.###v#.#.###.#\n";
    in << "#.....#...#...#.#.#...#\n";
    in << "#.#########.###.#.#.###\n";
    in << "#...###...#...#...#.###\n";
    in << "###.###.#.###v#####v###\n";
    in << "#...#...#.#.>.>.#.>.###\n";
    in << "#.###.###.#.###.#.#v###\n";
    in << "#.....###...###...#...#\n";
    in << "#####################.#\n";
//    ForestWalk fw(in);
    ForestWalk nm(in);
    ASSERT_EQ(nm.getLongestPath(), 94);
    ASSERT_EQ(nm.getLongestPath(false), 154);
}

TEST(Day23Test, Small) {
    std::stringstream in;
    in << "#.#####################\n";
    in << "#.....................#\n";
    in << "#########.###########.#\n";
    in << "#########.##....#####.#\n";
    in << "#########.##.##.#####.#\n";
    in << "#########....##.......#\n";
    in << "#####################.#\n";
    in << "#####################.#\n";
//    ForestWalk fw(in);
//    ASSERT_EQ(fw.getLongestPath(), 94);
    ForestWalk nm(in);
    ASSERT_EQ(nm.getLongestPath(false), 31);
}






















