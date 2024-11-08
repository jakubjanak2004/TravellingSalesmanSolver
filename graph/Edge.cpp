//
// Created by Jakub Janak on 9/14/24.
//

#include "Edge.h"

Edge::Edge(Node *sourceNode, Node *targetNode, const double weight){
    this->sourceNode = sourceNode;
    this->targetNode = targetNode;
    this->weight = weight;
}

std::string Edge::to_string() const {
    return "< " + this->sourceNode->to_string() + " -> " + this->targetNode->to_string() + " w: " +
           std::to_string(this->weight);
}

bool Edge::operator<(const Edge &e) const {
    return this->weight < e.weight;
}

bool Edge::operator>(const Edge &e) const {
    return this->weight > e.weight;
}

Node* Edge::get_source_node() const {
    return this->sourceNode;
}

Node* Edge::get_target_node() const {
    return this->targetNode;
}

double Edge::get_weight() const {
    return this->weight;
}
