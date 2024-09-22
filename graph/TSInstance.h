//
// Created by Jakub Janak on 9/14/24.
//

#ifndef TSINSTANCE_H
#define TSINSTANCE_H

#include "Graph.h"

#include <mutex>
#include <thread>


class TSInstance : public Graph {
    std::mutex m_1; // mutex for thread safety of minCost
    double minCost; // thread save minimal cost variable
    bool solved;
    Node startingNode;
    std::vector<Node> nodesExplored;
    std::vector<std::vector<Node> > bestHamiltonianPaths;
    std::chrono::duration<long long, std::ratio<1, 1000000000> > elapsed{};

public:
    TSInstance(std::vector<std::unique_ptr<Node> > nodes, std::vector<std::unique_ptr<Edge> > edges);

    static std::unique_ptr<TSInstance> createSyntheticInstance(int numOfNodes);

    std::vector<std::vector<Node> > solve(const std::string& args);

    void branch(std::vector<Node> visitedNodes, double cost, Node &currentNode);

    void branchParallel(std::vector<Node> visitedNodes, double cost, Node &currentNode, int numberOfThreads);

    [[nodiscard]] std::vector<std::vector<Node>> bruteForceSolve() const;

    [[nodiscard]] double getLowerBound(std::vector<Node> subPath) const;

    [[nodiscard]] double heuristicCombo() const;

    [[nodiscard]] double getMinCost();

    [[nodiscard]] bool isSolved() const;

    void setMinCost(double minCost);

    void printStatistics() const;

    void saveAs(const std::string &fileName) const;

    [[nodiscard]] std::string toString() const;
};


#endif //TSINSTANCE_H
