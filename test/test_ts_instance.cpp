#include "catch.hpp"
#include "../graph/ts_instance.hpp"
#include "../helper/Helper.hpp"

TEST_CASE("Test Solve Correctness", "[all]") {
    std::unique_ptr<ts_instance> instance;
    SECTION("K(5)") {
        instance = ts_instance::create_synthetic_instance(5);
        const std::set<std::vector<node> > solveResult = helper::convert_to_node_set(instance->solve());
        const std::set<std::vector<node> > bruteForceResult = helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(6)") {
        instance = ts_instance::create_synthetic_instance(6);
        const std::set<std::vector<node> > solveResult = helper::convert_to_node_set(instance->solve());
        const std::set<std::vector<node> > bruteForceResult = helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(7)") {
        instance = ts_instance::create_synthetic_instance(7);
        const std::set<std::vector<node> > solveResult = helper::convert_to_node_set(instance->solve());
        const std::set<std::vector<node> > bruteForceResult = helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(8)") {
        instance = ts_instance::create_synthetic_instance(8);
        const std::set<std::vector<node> > solveResult = helper::convert_to_node_set(instance->solve());
        const std::set<std::vector<node> > bruteForceResult = helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(9)") {
        instance = ts_instance::create_synthetic_instance(9);
        const std::set<std::vector<node> > solveResult = helper::convert_to_node_set(instance->solve());
        const std::set<std::vector<node> > bruteForceResult = helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
}

TEST_CASE("Test Solve Parallel Correctness", "[all]") {
    std::unique_ptr<ts_instance> instance;
    SECTION("K(5)") {
        instance = ts_instance::create_synthetic_instance(5);
        const std::set<std::vector<node> > solveResult = helper::convert_to_node_set(instance->solve(10));
        const std::set<std::vector<node> > bruteForceResult = helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(6)") {
        instance = ts_instance::create_synthetic_instance(6);
        const std::set<std::vector<node> > solveResult = helper::convert_to_node_set(instance->solve(10));
        const std::set<std::vector<node> > bruteForceResult = helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(7)") {
        instance = ts_instance::create_synthetic_instance(7);
        const std::set<std::vector<node> > solveResult = helper::convert_to_node_set(instance->solve(10));
        const std::set<std::vector<node> > bruteForceResult = helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(8)") {
        instance = ts_instance::create_synthetic_instance(8);
        const std::set<std::vector<node> > solveResult = helper::convert_to_node_set(instance->solve(10));
        const std::set<std::vector<node> > bruteForceResult = helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(9)") {
        instance = ts_instance::create_synthetic_instance(9);
        const std::set<std::vector<node> > solveResult = helper::convert_to_node_set(instance->solve(10));
        const std::set<std::vector<node> > bruteForceResult = helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
}
