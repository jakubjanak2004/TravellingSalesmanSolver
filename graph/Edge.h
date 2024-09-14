//
// Created by Jakub Janak on 9/14/24.
//

#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

#include <iostream>

class Node;

class Edge {
    Node* sourceNode;
    Node* targetNode;
    double weight;

public:
    Edge(Node* sourceNode, Node* targetNode, double weight);

    std::string toString() const;

    bool operator<(const Edge &e) const;

    bool operator>(const Edge &e) const;

    Node getTargetNode() const;

    double getWeight() const;
};


#endif //EDGE_H
