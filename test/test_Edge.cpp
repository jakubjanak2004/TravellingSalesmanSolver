#include "catch.hpp"
#include "../graph/Edge.hpp"

TEST_CASE("Test The Operators '>' and '<'", "[all]") {
    Node n1 = Node("A");
    Node n2 = Node("B");
    SECTION("e1 < e2 and e2 > e1 is true") {
        Edge e1 = Edge(&n1, &n2, 1);
        Edge e2 = Edge(&n2, &n1, 2);
        REQUIRE(e1 < e2);
        REQUIRE(e2 > e1);
    }
    SECTION("e1 > e2 and e2 < e1 is true") {
        Edge e1 = Edge(&n1, &n2, 2);
        Edge e2 = Edge(&n2, &n1, 1);
        REQUIRE(e1 > e2);
        REQUIRE(e2 < e1);
    }
}
