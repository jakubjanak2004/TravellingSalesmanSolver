//
// Created by Jakub Janak on 9/19/24.
//

#include "catch.hpp"
#include "../graph/TSInstance.h"

// ------------------------------------------------ HELPER FUNCTIONS -------------------------------------
std::set<std::vector<Node> > convert_to_node_set(const std::vector<std::vector<Node> > &paths) {
    std::set<std::vector<Node> > nodeSet;
    for (const auto &path: paths) {
        nodeSet.insert(path);
    }
    return nodeSet;
}

// ------------------------------------------------ TESTS ------------------------------------------------
TEST_CASE("Test Solve Correctness", "[all]") {
    std::unique_ptr<TSInstance> instance;
    SECTION("K(5)") {
        instance = TSInstance::create_synthetic_instance(5);
        const std::set<std::vector<Node> > solveResult = convert_to_node_set(instance->solve(""));
        const std::set<std::vector<Node> > bruteForceResult = convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(6)") {
        instance = TSInstance::create_synthetic_instance(6);
        const std::set<std::vector<Node> > solveResult = convert_to_node_set(instance->solve(""));
        const std::set<std::vector<Node> > bruteForceResult = convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(7)") {
        instance = TSInstance::create_synthetic_instance(7);
        const std::set<std::vector<Node> > solveResult = convert_to_node_set(instance->solve(""));
        const std::set<std::vector<Node> > bruteForceResult = convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(8)") {
        instance = TSInstance::create_synthetic_instance(8);
        const std::set<std::vector<Node> > solveResult = convert_to_node_set(instance->solve(""));
        const std::set<std::vector<Node> > bruteForceResult = convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(9)") {
        instance = TSInstance::create_synthetic_instance(9);
        const std::set<std::vector<Node> > solveResult = convert_to_node_set(instance->solve(""));
        const std::set<std::vector<Node> > bruteForceResult = convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
}

TEST_CASE("Test Solve Parallel Correctness", "[all]") {
    std::unique_ptr<TSInstance> instance;
    SECTION("K(5)") {
        instance = TSInstance::create_synthetic_instance(5);
        const std::set<std::vector<Node> > solveResult = convert_to_node_set(instance->solve("p"));
        const std::set<std::vector<Node> > bruteForceResult = convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(6)") {
        instance = TSInstance::create_synthetic_instance(6);
        const std::set<std::vector<Node> > solveResult = convert_to_node_set(instance->solve("p"));
        const std::set<std::vector<Node> > bruteForceResult = convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(7)") {
        instance = TSInstance::create_synthetic_instance(7);
        const std::set<std::vector<Node> > solveResult = convert_to_node_set(instance->solve("p"));
        const std::set<std::vector<Node> > bruteForceResult = convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(8)") {
        instance = TSInstance::create_synthetic_instance(8);
        const std::set<std::vector<Node> > solveResult = convert_to_node_set(instance->solve("p"));
        const std::set<std::vector<Node> > bruteForceResult = convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
    SECTION("K(9)") {
        instance = TSInstance::create_synthetic_instance(9);
        const std::set<std::vector<Node> > solveResult = convert_to_node_set(instance->solve("p"));
        const std::set<std::vector<Node> > bruteForceResult = convert_to_node_set(instance->brute_force_solve());

        REQUIRE(solveResult == bruteForceResult);
    }
}
