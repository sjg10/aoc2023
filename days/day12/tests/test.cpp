#include <gtest/gtest.h>
#include "Day12.h"
#include "SpringMap.h"
// Demonstrate some basic assertions for new class.

TEST(Day12Test, Part1Part2) {
    std::stringstream in;
    in << "???.### 1,1,3\n";
    in << ".??..??...?##. 1,1,3\n";
    in << "?#?#?#?#?#?#?#? 1,3,1,6\n";
    in << "????.#...#... 4,1,1\n";
    in << "????.######..#####. 1,6,5\n";
    in << "?###???????? 3,2,1\n";
    SpringMap sm(in);
    auto ret = sm.getValidOptionsSum();
    ASSERT_EQ(ret.first, 21);
    //ASSERT_EQ(ret.second, 0);
}