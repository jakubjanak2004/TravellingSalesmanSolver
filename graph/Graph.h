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
    Graph(std::vector<Node> nodes, std::vector<Edge> edges);

    double getCostBetweenNodes(Node &node1, Node &node2);

protected:
    std::vector<Node> nodes;
    std::vector<Edge> edges;
};


#endif //GRAPH_H
