//
// Created by Jakub Janak on 9/14/24.
//

#ifndef EDGE_H
#define EDGE_H

#include <iostream>

#include "Node.h"

class Edge {
    Node *sourceNode;
    Node *targetNode;
    double weight{};

public:
    Edge(Node *sourceNode, Node *targetNode, double weight);

    [[nodiscard]] std::string to_string() const;

    bool operator<(const Edge &e) const;

    bool operator>(const Edge &e) const;

    [[nodiscard]] Node *get_source_node() const;

    [[nodiscard]] Node *get_target_node() const;

    [[nodiscard]] double get_weight() const;
};


#endif //EDGE_H
