//
// Created by Jakub Janak on 9/14/24.
//

#ifndef NODE_H
#define NODE_H

// #include "Edge.h"

#include <string>
#include <vector>
#include <set>

class Edge;

class Node {
    std::string name;
    std::vector<Edge*> edges;

public:
    Node(std::string name);

    void addEdge(Edge* edge);

    [[nodiscard]] std::string toString() const;

    bool operator<(const Node &other) const;
    bool operator>(const Node &other) const;
    bool operator==(const Node &other) const;

    std::vector<Node*> getNeighbourNodes() const;
    std::vector<Edge*> getEdges();
};


#endif //NODE_H
