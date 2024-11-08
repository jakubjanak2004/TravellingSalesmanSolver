//
// Created by Jakub Janak on 11/8/24.
//

#include "catch.hpp"
#include "../graph/Node.h"

TEST_CASE("Test the operators '<' and '>'", "[all]") {
    Node n1 = Node("a");
    Node n2 =  Node("aa");
    Node n3 = Node("ab");
    Node n4 = Node("b");
    SECTION("'a' < 'aa' should be true, testing both < and >") {
        REQUIRE(n1 < n2);
        REQUIRE(n2 > n1);
    }
    SECTION("'a' < 'b' should be true, testing both < and >") {
        REQUIRE(n1 < n4);
        REQUIRE(n4 > n1);
    }
    SECTION("'aa' < 'ab' should be true, testing both < and >") {
        REQUIRE(n2 < n3);
        REQUIRE(n3 > n2);
    }
}

TEST_CASE("Test the operators '==' and '!='", "[all]") {
    Node n1 = Node("a");
    Node n2 = Node("b");
    SECTION("Node should be equal with itself") {
        REQUIRE(n1 == n1);
        REQUIRE_FALSE(n1 != n1);
    }
    SECTION("Node should not be equal with node with different name") {
        REQUIRE(n1 != n2);
        REQUIRE_FALSE(n1 == n2);
    }
}