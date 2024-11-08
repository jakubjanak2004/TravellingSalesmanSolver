//
// Created by Jakub Janak on 9/14/24.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Edge.h"

#include <vector>


class Graph {
public:
    Graph(std::vector<std::unique_ptr<Node>> nodes, std::vector<std::unique_ptr<Edge>> edges);

    [[nodiscard]] static double get_cost_between_nodes(Node &node1, const Node &node2);
    [[nodiscard]] static double get_cost_of_sub_path(std::vector<Node> subPath);
    [[nodiscard]] static double get_cost_of_ham_path(std::vector<Node> HamPath);

    [[nodiscard]] const std::vector<std::unique_ptr<Node>>& get_nodes() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Edge>>& get_edges() const;

protected:
    std::vector<std::unique_ptr<Node> > nodes;
    std::vector<std::unique_ptr<Edge> > edges;
};


#endif //GRAPH_H
