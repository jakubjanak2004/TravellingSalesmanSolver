//
// Created by Jakub Janak on 9/14/24.
//

#include "Edge.h"

Edge::Edge(Node *sourceNode, Node *targetNode, double weight) {
    this->sourceNode = sourceNode;
    this->targetNode = targetNode;
    this->weight = weight;
}

std::string Edge::toString() const {
    return "< " + this->sourceNode->toString() + " -- " + this->targetNode->toString() + " w: " +
           std::to_string(this->weight);
}

bool Edge::operator<(const Edge &e) const {
    return this->weight < e.weight;
}

bool Edge::operator>(const Edge &e) const {
    return this->weight > e.weight;
}

Node Edge::getTargetNode() const {
    return *this->targetNode;
}

double Edge::getWeight() const {
    return this->weight;
}
