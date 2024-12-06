#include "catch.hpp"
#include "../graph/graph.hpp"

TEST_CASE("Test Constructor", "[all]") {
    SECTION("empty nodes vector should throw invalid_argument") {
        std::vector<std::shared_ptr<node> > nodes = {};
        std::vector<std::shared_ptr<edge> > edges = {};
        REQUIRE_THROWS_AS([&]() { graph(std::move(nodes), std::move(edges)); }(), std::invalid_argument);
    }
}

TEST_CASE("get cost between nodes should return the weight of an edge between two nodes", "[all]") {
    std::shared_ptr<node> n1 = std::make_shared<node>("n1");
    std::shared_ptr<node> n2 = std::make_shared<node>("n2");
    std::shared_ptr<edge> e = std::make_shared<edge>(n1.get(), n2.get(), 5);

    n1->add_edge(e.get());
    n2->add_edge(e.get());

    std::vector nodes = {n1, n2};
    std::vector edges = {e};

    graph g = graph(std::move(nodes), std::move(edges));
    SECTION("cost should be 5") {
        REQUIRE(g.get_cost_between_nodes(*n1, *n2) == 5);
    }
}

TEST_CASE("get cost of sub path gets the correct cost of sub path", "[all]") {
    std::shared_ptr<node> n1 = std::make_shared<node>("n1");
    std::shared_ptr<node> n2 = std::make_shared<node>("n2");
    std::shared_ptr<node> n3 = std::make_shared<node>("n3");
    std::shared_ptr<node> n4 = std::make_shared<node>("n4");

    std::shared_ptr e1 = std::make_shared<edge>(n1.get(), n2.get(), 4);
    std::shared_ptr e2 = std::make_shared<edge>(n2.get(), n3.get(), 6);
    std::shared_ptr e3 = std::make_shared<edge>(n3.get(), n4.get(), 8);
    std::shared_ptr e4 = std::make_shared<edge>(n4.get(), n1.get(), 5);

    n1->add_edge(e1.get());
    n1->add_edge(e4.get());

    n2->add_edge(e1.get());
    n2->add_edge(e2.get());

    n3->add_edge(e2.get());
    n3->add_edge(e3.get());

    n4->add_edge(e3.get());
    n4->add_edge(e4.get());

    std::vector nodes = {n1, n2, n3, n4};
    std::vector edges = {e1, e2, e3, e4};
    std::vector sub_path = {*n1, *n2, *n3};
    graph g = graph(nodes, edges);
    SECTION("cost should be 10") {
        REQUIRE(g.get_cost_of_sub_path(sub_path) == 10);
    }
}

TEST_CASE("get cost of ham path should return the correct cost of hamiltonian path", "[all]") {
    std::shared_ptr<node> n1 = std::make_shared<node>("n1");
    std::shared_ptr<node> n2 = std::make_shared<node>("n2");
    std::shared_ptr<node> n3 = std::make_shared<node>("n3");
    std::shared_ptr<node> n4 = std::make_shared<node>("n4");

    std::shared_ptr e1 = std::make_shared<edge>(n1.get(), n2.get(), 4);
    std::shared_ptr e2 = std::make_shared<edge>(n2.get(), n3.get(), 6);
    std::shared_ptr e3 = std::make_shared<edge>(n3.get(), n4.get(), 8);
    std::shared_ptr e4 = std::make_shared<edge>(n4.get(), n1.get(), 5);

    n1->add_edge(e1.get());
    n1->add_edge(e4.get());

    n2->add_edge(e1.get());
    n2->add_edge(e2.get());

    n3->add_edge(e2.get());
    n3->add_edge(e3.get());

    n4->add_edge(e3.get());
    n4->add_edge(e4.get());

    std::vector nodes = {n1, n2, n3, n4};
    std::vector edges = {e1, e2, e3, e4};
    std::vector path = {*n1, *n2, *n3, *n4};
    graph g = graph(nodes, edges);
    SECTION("cost should be 23") {
        REQUIRE(g.get_cost_of_ham_path(path) == 23);
    }
}