#include <gtest/gtest.h>
#include "Day15.h"
// Demonstrate some basic assertions for new class.
TEST(Day15Test, Part1Part2) {
    ASSERT_EQ(Day15::HASH("HASH"), 52);
    ASSERT_EQ(Day15::HASH("rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7\n"), 1320);
    ASSERT_EQ(Day15::HASH2("rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7\n"), 145);
}
