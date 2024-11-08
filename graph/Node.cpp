//
// Created by Jakub Janak on 9/14/24.
//

#include "Node.h"

#include "Edge.h"

Node::Node(std::string name) {
    this->name = std::move(name);
}

void Node::add_edge(Edge* edge) {
    int addingIndex = 0;
    for (const auto &loopEdge : this->edges) {
        if (loopEdge->get_weight() < edge->get_weight()) {
            addingIndex++;
        }
    }
    this->edges.insert(edges.begin() + addingIndex, edge);
}

std::string Node::to_string() const {
    return this->name;
}

bool Node::operator<(const Node &other) const {
    return this->name < other.name;
}

bool Node::operator>(const Node &other) const {
    return this->name > other.name;
}

bool Node::operator==(const Node &other) const {
    return this->name == other.name;
}

bool Node::operator!=(const Node &other) const {
    return this->name != other.name;
}

std::vector<Node*> Node::get_neighbour_nodes() const {
    std::vector<Node*> neighbours;
    neighbours.reserve(this->edges.size());
    for (const Edge* edge : this->edges) {
        neighbours.push_back(edge->get_target_node());
    }
    return neighbours;
}

std::vector<Edge*> Node::get_edges() const {
    return this->edges;
}

std::string Node::get_name() {
    return this->name;
}