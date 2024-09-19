//
// Created by Jakub Janak on 9/14/24.
//

#ifndef TSINSTANCE_H
#define TSINSTANCE_H

#include "Graph.h"


class TSInstance : public Graph {
    double minCost;
    Node startingNode;
    std::vector<Node> nodesExplored;
    std::vector<std::vector<Node> > bestHamiltonianPaths;
    std::chrono::duration<long long, std::ratio<1, 1000000000> > elapsed{};

public:
    TSInstance(std::vector<std::unique_ptr<Node> > nodes, std::vector<std::unique_ptr<Edge> > edges);

    static TSInstance createSyntheticInstance(int numOfNodes);

    std::vector<std::vector<Node> > solve();

    std::vector<std::vector<Node>> bruteForceSolve() const;

    void branch(std::vector<Node> visitedNodes, double cost, Node &currentNode);

    [[nodiscard]] double getLowerBound(std::vector<Node> subPath) const;

    [[nodiscard]] double heuristicCombo() const;

    [[nodiscard]] double getMinCost() const;

    void printStatistics() const;

    void saveAs(const std::string &fileName) const;

    [[nodiscard]] std::string toString() const;
};


#endif //TSINSTANCE_H
