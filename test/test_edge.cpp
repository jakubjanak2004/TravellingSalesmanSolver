#include "catch.hpp"
#include "../graph/edge.hpp"

TEST_CASE("Test The Operators '>' and '<'", "[all]") {
    node n1 = node("A");
    node n2 = node("B");
    SECTION("e1 < e2 and e2 > e1 is true") {
        edge e1 = edge(&n1, &n2, 1);
        edge e2 = edge(&n2, &n1, 2);
        REQUIRE(e1 < e2);
        REQUIRE(e2 > e1);
    }
    SECTION("e1 > e2 and e2 < e1 is true") {
        edge e1 = edge(&n1, &n2, 2);
        edge e2 = edge(&n2, &n1, 1);
        REQUIRE(e1 > e2);
        REQUIRE(e2 < e1);
    }
}
