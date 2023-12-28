#include <gtest/gtest.h>
#include "BlockFall.h"

// Demonstrate some basic assertions for new class.
TEST(Day22Test, Part1Part2) {
    std::stringstream in;
    in << "1,1,12~1,1,13\n";
    in << "1,0,1~1,2,1\n";
    in << "0,0,2~2,0,2\n";
    in << "0,2,3~2,2,3\n";
    in << "0,0,4~0,2,4\n";
    in << "2,0,5~2,2,5\n";
    in << "0,1,6~2,1,6\n";
    in << "1,1,8~1,1,9\n";
    BlockField bf(in);
    auto ret = bf.getRemovable();
    ASSERT_EQ(ret.first, 5);
    ASSERT_EQ(ret.second, 10);
}

