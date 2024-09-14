//
// Created by Jakub Janak on 9/14/24.
//

#include "TSInstance.h"
#include "Node.h"

TSInstance::TSInstance(std::vector<Node> nodes, std::vector<Edge> edges)
    : Graph(std::move(nodes), std::move(edges)),
      minCost(std::numeric_limits<double>::max()),
      startingNode(this->nodes[0]) {
}

std::vector<std::vector<Node> > TSInstance::solve() {
    std::vector visitedNodes = {this->startingNode};
    branch(visitedNodes, 0, this->startingNode);
    return this->bestHamiltonians;
}

void TSInstance::branch(std::vector<Node> visitedNodes, double cost, Node currentNode) {
    std::vector<Node> visitedNodesCopied = visitedNodes;

    std::vector<Node> neighbours = currentNode.getNeighbourNodes();
    for (Node &neighbour: neighbours) {
        if (std::find(visitedNodes.begin(), visitedNodes.end(), neighbour) != visitedNodes.end()) {
            continue;
        }

        std::vector<Node> branchVisNodes = visitedNodesCopied;
        branchVisNodes.push_back(neighbour);

        branch(branchVisNodes, cost + this->getCostBetweenNodes(currentNode, neighbour), neighbour);
    }

    if (visitedNodes.size() == this->nodes.size() - 1) {
        cost += this->getCostBetweenNodes(visitedNodes.back(), startingNode);
        if (cost < this->minCost) {
            this->minCost = cost;
            this->bestHamiltonians.clear();
            this->bestHamiltonians.push_back(visitedNodes);
        } else if (cost == this->minCost) {
            this->bestHamiltonians.push_back(visitedNodes);
        }
    }
}

double TSInstance::getMinCost() {
    return this->minCost;
}
