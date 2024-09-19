//
// Created by Jakub Janak on 9/14/24.
//

#include "Graph.h"

Graph::Graph(std::vector<std::unique_ptr<Node>> nodes, std::vector<std::unique_ptr<Edge>> edges)
    : nodes(std::move(nodes)), edges(std::move(edges)) {
    if (this->nodes.empty()) {
        throw std::invalid_argument("Nodes vector cannot be empty!");
    }
}

double Graph::getCostBetweenNodes(Node &node1, const Node &node2) {
    for(const Edge* edge : node1.getEdges()) {
        if (*edge->getTargetNode() == node2) {
            return edge->getWeight();
        }
    }
    return std::numeric_limits<double>::infinity();
}

double Graph::getCostOfSubPath(std::vector<Node> subPath) {
    double cost = 0;
    for (int i = 0; i < subPath.size() - 1; i++) {
        cost += getCostBetweenNodes(subPath[i], subPath[i + 1]);
    }
    return cost;
}

const std::vector<std::unique_ptr<Node>>& Graph::getNodes() const {
    return this->nodes;
}

const std::vector<std::unique_ptr<Edge>>& Graph::getEdges() const {
    return this->edges;
}

