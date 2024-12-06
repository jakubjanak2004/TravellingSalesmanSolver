#include "catch.hpp"
#include "../graph/Edge.h"
#include "../graph/Node.h"

TEST_CASE("Get neighbour nodes should get nodes connected to our node with an edge") {
    Node n1 = Node("a");
    Node n2 = Node("b");
    Node n3 = Node("not connected");
    Edge e1 = Edge(&n1, &n2, 1);
    Edge e2 = Edge(&n2, &n1, 1);
    n1.add_edge(&e1);
    n1.add_edge(&e2);
    n2.add_edge(&e1);
    n2.add_edge(&e2);
    SECTION("n2 should be a neighbour to n1") {
        const auto& n1_neighbours = n1.get_neighbour_nodes();
        REQUIRE(std::find(n1_neighbours.begin(), n1_neighbours.end(), &n2) != n1_neighbours.end());
        REQUIRE_FALSE(std::find(n1_neighbours.begin(), n1_neighbours.end(), &n3) != n1_neighbours.end());
    }
    SECTION("n1 should be a neighbour to n2") {
        const auto& n2_neighbours = n2.get_neighbour_nodes();
        REQUIRE(std::find(n2_neighbours.begin(), n2_neighbours.end(), &n1) != n2_neighbours.end());
        REQUIRE_FALSE(std::find(n2_neighbours.begin(), n2_neighbours.end(), &n3) != n2_neighbours.end());
    }
    SECTION("n1 and n2 should not be a neighbour of n3") {
        const auto& n3_neighbours = n3.get_neighbour_nodes();
        REQUIRE_FALSE(std::find(n3_neighbours.begin(), n3_neighbours.end(), &n1) != n3_neighbours.end());
        REQUIRE_FALSE(std::find(n3_neighbours.begin(), n3_neighbours.end(), &n2) != n3_neighbours.end());
    }
}

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