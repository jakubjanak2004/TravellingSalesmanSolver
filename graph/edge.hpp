#ifndef EDGE_H
#define EDGE_H

#include <iostream>

#include "node.hpp"

class edge {
    node *sourceNode;
    node *targetNode;
    double weight{};

public:
    edge(node *sourceNode, node *targetNode, double weight);

    [[nodiscard]] std::string to_string() const;

    bool operator<(const edge &e) const;

    bool operator>(const edge &e) const;

    [[nodiscard]] node *get_source_node() const;

    [[nodiscard]] node *get_target_node() const;

    [[nodiscard]] double get_weight() const;
};


#endif //EDGE_H
