#include "graph/Node.h"
#include "graph/Edge.h"
#include "graph/TSInstance.h"

#include <iostream>
#include <random>

int getRandomInteger(int from, int to);

void printEdges(std::vector<Node> nodes);

void printPaths(std::vector<std::vector<Node> > tsSolution);

int main() {
    std::cout << "**********TSP Solver**********" << std::endl;

    // vectors of nodes and edges
    std::vector<Node> nodes;
    std::vector<Edge> edges;

    // creating nodes
    nodes.emplace_back("A");
    nodes.emplace_back("B");
    nodes.emplace_back("C");
    nodes.emplace_back("D");
    nodes.emplace_back("E");
    nodes.emplace_back("F");
    nodes.emplace_back("G");
    nodes.emplace_back("H");

    // setting the edges between nodes (graph is oriented)
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes.size(); j++) {
            if (i < j) {
                Edge edge1 = Edge(&nodes[i], &nodes[j], getRandomInteger(1, 10));
                nodes[i].addEdge(edge1);
                Edge edge2 = Edge(&nodes[j], &nodes[i], getRandomInteger(1, 10));
                nodes[j].addEdge(edge2);
                edges.push_back(edge1);
                edges.push_back(edge2);
            }
        }
    }

    // creating the instance of the problem
    TSInstance tsInstance = TSInstance(nodes, edges);

    // starting the solver
    std::cout << "Starting TSP Solver..." << std::endl;
    std::vector<std::vector<Node> > tsSolution = tsInstance.solve();

    // printing statistics about the solution
    std::cout << "Travelling Salesman solution size: " << tsSolution.size() << std::endl;
    std::cout << "The optimal path length: " << tsInstance.getMinCost() << std::endl;

    // printing optimal paths
    // printPaths(tsSolution);

    // printing the edges to check correctness
    // printEdges(nodes);
}

int getRandomInteger(int from, int to) {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution intDist(from, to);

    return intDist(rng);
}

void printEdges(std::vector<Node> nodes) {
    for (Node node: nodes) {
        for (Edge edge: node.getEdges()) {
            std::cout << edge.toString() << " ";
        }
        std::cout << std::endl;
    }
}

void printPaths(std::vector<std::vector<Node> > tsSolution) {
    std::cout << "Best Paths:" << std::endl;
    for (std::vector<Node> path: tsSolution) {
        for (Node node: path) {
            std::cout << node.toString() << " ";
        }
        std::cout << std::endl;
    }
}
