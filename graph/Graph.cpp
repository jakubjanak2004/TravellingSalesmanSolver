//
// Created by Jakub Janak on 9/14/24.
//

#include "Graph.h"

Graph::Graph(std::vector<Node> nodes, std::vector<Edge> edges) {
    if (nodes.empty()) {
        throw std::invalid_argument("Nodes vector cannot be empty!");
    }
    this->nodes = nodes;
    this->edges = edges;
}

double Graph::getCostBetweenNodes(Node &node1, Node &node2) {
    for( const Edge &edge : node1.getEdges()) {
        if (edge.getTargetNode() == node2) {
            return edge.getWeight();
        }
    }
    return std::numeric_limits<double>::max();
}

