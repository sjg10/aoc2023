#include <gtest/gtest.h>
#include "MachineSort.h"
// Demonstrate some basic assertions for new class.
TEST(Day19Test, Part1Part2) {
    std::stringstream in;
    in << "px{a<2006:qkq,m>2090:A,rfg}\n";
    in << "pv{a>1716:R,A}\n";
    in << "lnx{m>1548:A,A}\n";
    in << "rfg{s<537:gd,x>2440:R,A}\n";
    in << "qs{s>3448:A,lnx}\n";
    in << "qkq{x<1416:A,crn}\n";
    in << "crn{x>2662:A,R}\n";
    in << "in{s<1351:px,qqz}\n";
    in << "qqz{s>2770:qs,m<1801:hdj,R}\n";
    in << "gd{a>3333:R,R}\n";
    in << "hdj{m>838:A,pv}\n";
    in << "\n";
    in << "{x=787,m=2655,a=1222,s=2876}\n";
    in << "{x=1679,m=44,a=2067,s=496}\n";
    in << "{x=2036,m=264,a=79,s=2244}\n";
    in << "{x=2461,m=1339,a=466,s=291}\n";
    in << "{x=2127,m=1623,a=2188,s=1013}\n";
    MachineSort ms(in);
    ASSERT_EQ(ms.sort(), 19114);
    ASSERT_EQ(ms.sort2(), 167409079868000);
}

