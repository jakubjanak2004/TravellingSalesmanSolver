//
// Created by Jakub Janak on 9/19/24.
//

#include <gtest/gtest.h>
#include "../graph/TSInstance.h"
#include <memory>

// Utility function
std::set<std::vector<Node>> convertToNodeSet(const std::vector<std::vector<Node>>& paths) {
    std::set<std::vector<Node>> nodeSet;
    for (const auto& path : paths) {
        nodeSet.insert(path);
    }
    return nodeSet;
}

class SolveMethodResultTest : public ::testing::TestWithParam<int> {
protected:
    std::unique_ptr<TSInstance> instance;

    void SetUp() override {
        const int numNodes = GetParam();
        instance = std::make_unique<TSInstance>(TSInstance::createSyntheticInstance(numNodes));
    }
};

TEST_P(SolveMethodResultTest, SolutionCorrectness) {
    const std::set<std::vector<Node>> solveResult = convertToNodeSet(instance->solve(""));
    const std::set<std::vector<Node>> bruteForceResult = convertToNodeSet(instance->bruteForceSolve());

    ASSERT_EQ(solveResult, bruteForceResult);
}

INSTANTIATE_TEST_SUITE_P(
    VariousNodeCounts,
    SolveMethodResultTest,
    ::testing::Values(3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9)
);
