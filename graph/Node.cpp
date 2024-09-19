//
// Created by Jakub Janak on 9/14/24.
//

#include "Node.h"

#include "Edge.h"

Node::Node(std::string name) {
    this->name = std::move(name);
}

void Node::addEdge(Edge* edge) {
    int addingIndex = 0;
    for (const auto &loopEdge : this->edges) {
        if (loopEdge->getWeight() < edge->getWeight()) {
            addingIndex++;
        }
    }
    this->edges.insert(edges.begin() + addingIndex, edge);
}

std::string Node::toString() const {
    return this->name;
}

bool Node::operator<(const Node &other) const {
    return this->name < other.name;
}

bool Node::operator>(const Node &other) const {
    return this->name < other.name;
}

bool Node::operator==(const Node &other) const {
    return this->name == other.name;
}

std::vector<Node*> Node::getNeighbourNodes() const {
    std::vector<Node*> neighbours;
    neighbours.reserve(this->edges.size());
    for (const Edge* edge : this->edges) {
        neighbours.push_back(edge->getTargetNode());
    }
    return neighbours;
}

std::vector<Edge*> Node::getEdges() {
    return this->edges;
}



