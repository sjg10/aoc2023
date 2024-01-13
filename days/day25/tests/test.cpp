#include <gtest/gtest.h>
#include "Day25.h"
#include "WiringMachine.h"
// Demonstrate some basic assertions for new class.
TEST(Day25Test, Part1) {
    std::stringstream in;
    in << "jqt: rhn xhk nvd\n";
    in << "rsh: frs pzl lsr\n";
    in << "xhk: hfx\n";
    in << "cmg: qnr nvd lhk bvb\n";
    in << "rhn: xhk bvb hfx\n";
    in << "bvb: xhk hfx\n";
    in << "pzl: lsr hfx nvd\n";
    in << "qnr: nvd\n";
    in << "ntq: jqt hfx bvb xhk\n";
    in << "nvd: lhk\n";
    in << "lsr: lhk\n";
    in << "rzs: qnr cmg lsr rsh\n";
    in << "frs: qnr lhk lsr\n";
    WiringMachine wm(in);
    ASSERT_EQ(wm.getScore(), 54);
}
