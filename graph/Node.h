//
// Created by Jakub Janak on 9/14/24.
//

#ifndef NODE_H
#define NODE_H

// #include "Edge.h"

#include <string>
#include <vector>

class Edge;

class Node {
    std::string name;
    std::vector<Edge *> edges;

public:
    explicit Node(std::string name);

    void add_edge(Edge *edge);

    [[nodiscard]] std::string to_string() const;

    bool operator<(const Node &other) const;

    bool operator>(const Node &other) const;

    bool operator==(const Node &other) const;

    bool operator!=(const Node &other) const;

    [[nodiscard]] std::vector<Node *> get_neighbour_nodes() const;

    [[nodiscard]] std::vector<Edge *> get_edges() const;

    std::string get_name();
};


#endif //NODE_H
