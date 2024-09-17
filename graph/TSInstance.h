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
    std::vector<std::vector<Node> > bestHamiltonians;
    std::chrono::duration<long long, std::ratio<1, 1000> > elapsed{};

public:
    TSInstance(std::vector<std::unique_ptr<Node> > nodes, std::vector<std::unique_ptr<Edge> > edges);

    std::vector<std::vector<Node> > solve();

    void branch(std::vector<Node> visitedNodes, double cost, Node &currentNode);

    double getLowerBound(std::vector<Node> subPath);

    double getCostOfSubPath(std::vector<Node> subPath);

    double getMinCost() const;

    void printStatistics() const;

    void saveAs(const std::string &fileName) const;
};


#endif //TSINSTANCE_H
