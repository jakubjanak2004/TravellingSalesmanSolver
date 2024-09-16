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

    double getCostBetweenNodes(Node &node1, Node &node2);

    [[nodiscard]] const std::vector<std::unique_ptr<Node>>& getNodes() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Edge>>& getEdges() const;

protected:
    std::vector<std::unique_ptr<Node> > nodes;
    std::vector<std::unique_ptr<Edge> > edges;
};


#endif //GRAPH_H
