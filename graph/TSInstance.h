//
// Created by Jakub Janak on 9/14/24.
//

#ifndef TSINSTANCE_H
#define TSINSTANCE_H

#include "Graph.h"


class TSInstance : Graph {
    double minCost;
    Node startingNode;
    std::vector<Node> nodesExplored;
    std::vector<std::vector<Node> > bestHamiltonians;

public:
    TSInstance(std::vector<Node> nodes, std::vector<Edge> edges);

    std::vector<std::vector<Node> > solve();

    void branch(std::vector<Node> visitedNodes, double cost, Node currentNode);

    double getMinCost();
};


#endif //TSINSTANCE_H
