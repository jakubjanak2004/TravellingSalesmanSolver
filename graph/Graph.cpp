//
// Created by Jakub Janak on 9/14/24.
//

#include "Graph.h"

#include <utility>

Graph::Graph(std::vector<std::unique_ptr<Node>> nodes, std::vector<std::unique_ptr<Edge>> edges)
    : nodes(std::move(nodes)), edges(std::move(edges)) {
    if (this->nodes.empty()) {
        throw std::invalid_argument("Nodes vector cannot be empty!");
    }
}

double Graph::getCostBetweenNodes(Node &node1, Node &node2) {
    for(const Edge* edge : node1.getEdges()) {
        if (*edge->getTargetNode() == node2) {
            return edge->getWeight();
        }
    }
    return std::numeric_limits<double>::infinity();
}

const std::vector<std::unique_ptr<Node>>& Graph::getNodes() const {
    return this->nodes;
}

const std::vector<std::unique_ptr<Edge>>& Graph::getEdges() const {
    return this->edges;
}

