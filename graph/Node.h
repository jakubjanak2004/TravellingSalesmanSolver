//
// Created by Jakub Janak on 9/14/24.
//

#ifndef NODE_H
#define NODE_H

#include "Edge.h"

#include <set>

class Edge;

class Node {
    std::string name;
    std::multiset<Edge> edges;

public:
    Node(std::string name);
    void addEdge(Edge &edge);

    [[nodiscard]] std::string toString() const;

    bool operator<(Node &other) const;

    bool operator>(Node &other) const;

    bool operator==(Node &other) const;

    std::vector<Node> getNeighbourNodes();

    std::multiset<Edge> getEdges();
};


#endif //NODE_H
