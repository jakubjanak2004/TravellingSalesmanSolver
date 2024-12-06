#include "edge.hpp"

edge::edge(node *sourceNode, node *targetNode, const double weight){
    this->sourceNode = sourceNode;
    this->targetNode = targetNode;
    this->weight = weight;
}

std::string edge::to_string() const {
    return "< " + this->sourceNode->to_string() + " -> " + this->targetNode->to_string() + " w: " +
           std::to_string(this->weight);
}

bool edge::operator<(const edge &e) const {
    return this->weight < e.weight;
}

bool edge::operator>(const edge &e) const {
    return this->weight > e.weight;
}

node* edge::get_source_node() const {
    return this->sourceNode;
}

node* edge::get_target_node() const {
    return this->targetNode;
}

double edge::get_weight() const {
    return this->weight;
}
