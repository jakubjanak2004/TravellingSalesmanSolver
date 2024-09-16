//
// Created by Jakub Janak on 9/14/24.
//

#ifndef EDGE_H
#define EDGE_H

#include <iostream>

#include "Node.h"

class Edge {
    Node* sourceNode;
    Node* targetNode;
    double weight{};

public:
    Edge(Node *sourceNode, Node *targetNode, double weight);

    [[nodiscard]] std::string toString() const;

    bool operator<(const Edge &e) const;
    bool operator>(const Edge &e) const;

    [[nodiscard]] Node* getTargetNode() const;

    [[nodiscard]] double getWeight() const;
};


#endif //EDGE_H
