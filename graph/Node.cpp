//
// Created by Jakub Janak on 9/14/24.
//

#include "Node.h"

Node::Node(std::string name) {
    this->name = name;
}

void Node::addEdge(Edge &edge) {
    this->edges.insert(edge);
}

std::string Node::toString() const {
    return this->name;
}

bool Node::operator<(Node &other) const {
    return this->name < other.name;
}

bool Node::operator>(Node &other) const {
    return this->name < other.name;
}

bool Node::operator==(Node &other) const {
    return this->name == other.name;
}

std::vector<Node> Node::getNeighbourNodes() {
    std::vector<Node> neighbours;
    for (const Edge &edge : this->edges) {
        neighbours.push_back(edge.getTargetNode());
    }
    return neighbours;
}

std::multiset<Edge> Node::getEdges() {
    return this->edges;
}



