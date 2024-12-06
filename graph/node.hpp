#ifndef NODE_H
#define NODE_H

// #include "Edge.h"

#include <string>
#include <vector>

class edge;

class node {
    std::string name;
    std::vector<edge *> edges;

public:
    explicit node(std::string name);

    void add_edge(edge *edge);

    [[nodiscard]] std::string to_string() const;

    bool operator<(const node &other) const;

    bool operator>(const node &other) const;

    bool operator==(const node &other) const;

    bool operator!=(const node &other) const;

    [[nodiscard]] std::vector<node *> get_neighbour_nodes() const;

    [[nodiscard]] std::vector<edge *> get_edges() const;

    std::string get_name();
};


#endif //NODE_H
