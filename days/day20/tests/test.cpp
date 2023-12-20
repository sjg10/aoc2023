#include <gtest/gtest.h>
#include "Day20.h"
#include "PulseGen.h"
// Demonstrate some basic assertions for new class.
TEST(Day20Test, Part1Part2) {
    std::stringstream in;
    in << "broadcaster -> a, b, c\n";
    in << "%a -> b\n";
    in << "%b -> c\n";
    in << "%c -> inv\n";
    in << "&inv -> a\n";
    PulseGen pg(in);
    auto r = pg.run();
    ASSERT_EQ(r.first, 32000000);
}

TEST(Day20Test, Part1Part2B) {
    std::stringstream in;
    in << "broadcaster -> a\n";
    in << "%a -> inv, con\n";
    in << "&inv -> b\n";
    in << "%b -> con\n";
    in << "&con -> output\n";
    PulseGen pg(in);
    auto r = pg.run();
    ASSERT_EQ(r.first, 11687500);
}