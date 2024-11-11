//
// Created by Jakub Janak on 9/19/24.
//

#include "catch.hpp"
#include "../graph/TSInstance.h"
#include "../helper/Helper.h"

TEST_CASE("Test Solve Correctness", "[all]") {
    std::unique_ptr<TSInstance> instance;
    SECTION("K(5)") {
        instance = TSInstance::create_synthetic_instance(5);
        const std::set<std::vector<Node> > solveResult = Helper::convert_to_node_set(instance->solve());
        const std::set<std::vector<Node> > bruteForceResult = Helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(6)") {
        instance = TSInstance::create_synthetic_instance(6);
        const std::set<std::vector<Node> > solveResult = Helper::convert_to_node_set(instance->solve());
        const std::set<std::vector<Node> > bruteForceResult = Helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(7)") {
        instance = TSInstance::create_synthetic_instance(7);
        const std::set<std::vector<Node> > solveResult = Helper::convert_to_node_set(instance->solve());
        const std::set<std::vector<Node> > bruteForceResult = Helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(8)") {
        instance = TSInstance::create_synthetic_instance(8);
        const std::set<std::vector<Node> > solveResult = Helper::convert_to_node_set(instance->solve());
        const std::set<std::vector<Node> > bruteForceResult = Helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(9)") {
        instance = TSInstance::create_synthetic_instance(9);
        const std::set<std::vector<Node> > solveResult = Helper::convert_to_node_set(instance->solve());
        const std::set<std::vector<Node> > bruteForceResult = Helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
}

TEST_CASE("Test Solve Parallel Correctness", "[all]") {
    std::unique_ptr<TSInstance> instance;
    SECTION("K(5)") {
        instance = TSInstance::create_synthetic_instance(5);
        const std::set<std::vector<Node> > solveResult = Helper::convert_to_node_set(instance->solve(10));
        const std::set<std::vector<Node> > bruteForceResult = Helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(6)") {
        instance = TSInstance::create_synthetic_instance(6);
        const std::set<std::vector<Node> > solveResult = Helper::convert_to_node_set(instance->solve(10));
        const std::set<std::vector<Node> > bruteForceResult = Helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(7)") {
        instance = TSInstance::create_synthetic_instance(7);
        const std::set<std::vector<Node> > solveResult = Helper::convert_to_node_set(instance->solve(10));
        const std::set<std::vector<Node> > bruteForceResult = Helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(8)") {
        instance = TSInstance::create_synthetic_instance(8);
        const std::set<std::vector<Node> > solveResult = Helper::convert_to_node_set(instance->solve(10));
        const std::set<std::vector<Node> > bruteForceResult = Helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(9)") {
        instance = TSInstance::create_synthetic_instance(9);
        const std::set<std::vector<Node> > solveResult = Helper::convert_to_node_set(instance->solve(10));
        const std::set<std::vector<Node> > bruteForceResult = Helper::convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
}
