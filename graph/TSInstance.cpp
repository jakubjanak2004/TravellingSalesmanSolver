//
// Created by Jakub Janak on 9/14/24.
//

#include "../files/FileManager.h"
#include "TSInstance.h"
#include "Node.h"

#include <sstream>

TSInstance::TSInstance(std::vector<std::unique_ptr<Node> > nodes, std::vector<std::unique_ptr<Edge> > edges)
    : Graph(std::move(nodes), std::move(edges)),
      minCost(std::numeric_limits<double>::infinity()),
      startingNode(*this->nodes[0]) {
}

std::vector<std::vector<Node> > TSInstance::solve() {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector visitedNodes = {this->startingNode};
    branch(visitedNodes, 0, this->startingNode);
    auto end = std::chrono::high_resolution_clock::now();
    this->elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return this->bestHamiltonians;
}

void TSInstance::branch(std::vector<Node> visitedNodes, double cost, Node &currentNode) {
    std::vector<Node *> neighbours = currentNode.getNeighbourNodes(); // causing segmentation from file manager
    for (Node *neighbour: neighbours) {
        if (std::find(visitedNodes.begin(), visitedNodes.end(), *neighbour) != visitedNodes.end()) {
            continue;
        }

        std::vector<Node> branchVisNodes = visitedNodes;
        branchVisNodes.push_back(*neighbour);

        if (this->getLowerBound(branchVisNodes) <= this->minCost) {
            branch(branchVisNodes, cost + this->getCostBetweenNodes(currentNode, *neighbour), *neighbour);
        }
    }

    if (visitedNodes.size() == this->nodes.size()) {
        cost += this->getCostBetweenNodes(visitedNodes.back(), startingNode);
        if (cost < this->minCost) {
            this->minCost = cost;
            this->bestHamiltonians.clear();
            this->bestHamiltonians.push_back(visitedNodes);
        } else if (cost == this->minCost) {
            this->bestHamiltonians.push_back(visitedNodes);
        }
    }
}

double TSInstance::getLowerBound(std::vector<Node> subPath) {
    double cost = this->getCostOfSubPath(subPath);

    for (auto &node: this->nodes) {
        if (std::find(subPath.begin(), subPath.end() - 1, *node) == subPath.end() - 1) {
            Edge *edge = *node->getEdges().begin();
            cost += edge->getWeight();
        }
    }
    return cost;
}

double TSInstance::getCostOfSubPath(std::vector<Node> subPath) {
    double cost = 0;
    for (int i = 0; i < subPath.size() - 1; i++) {
        cost += this->getCostBetweenNodes(subPath[i], subPath[i + 1]);
    }
    return cost;
}

double TSInstance::getMinCost() const {
    return this->minCost;
}

void TSInstance::printStatistics() const {
    std::cout << std::endl;
    std::cout << "Travelling Salesman Instance with: " << this->nodes.size() << " nodes" << std::endl;
    std::cout << "Solution set size: " << this->bestHamiltonians.size() << std::endl;
    std::cout << "The optimal path length: " << this->minCost << std::endl;
    std::cout << "Calculation took: " << elapsed.count() << " ms" << std::endl;

    std::cout << "First hamiltonian: ";
    for (const Node &node: this->bestHamiltonians.front()) {
        std::cout << node.toString() << " ";
    }
    std::cout << std::endl;
}

void TSInstance::saveAs(const std::string &fileName) const {
    std::ostringstream fileContent;
    fileContent << "digraph G {" << std::endl;
    for (auto &node: this->nodes) {
        fileContent << node->toString() << ";" << std::endl;
    }
    for (auto &edge: this->edges) {
        std::ostringstream weight;
        weight << std::defaultfloat << edge->getWeight();
        fileContent << edge->getSourceNode()->toString() << " -> " << edge->getTargetNode()->toString()
                << "[label=\"" << weight.str() << "\" weight=\"" << weight.str() << "\"";
        auto it1 = std::find(this->bestHamiltonians[0].begin(), this->bestHamiltonians[0].end(),
                             *edge->getSourceNode());
        auto it2 = std::find(this->bestHamiltonians[0].begin(), this->bestHamiltonians[0].end(),
                             *edge->getTargetNode());
        auto dis1 = std::distance(this->bestHamiltonians[0].begin(), it2);
        auto dis2 = std::distance(this->bestHamiltonians[0].begin(), it1);
        if (it1 != this->bestHamiltonians[0].end() && it2 != this->bestHamiltonians[0].end()) {
            if (dis1 - dis2 == 1) {
                fileContent << "color=\"red\"";
            }
            if (std::distance(this->bestHamiltonians[0].begin(), it1) == this->bestHamiltonians[0].size()-1 && std::distance(this->bestHamiltonians[0].begin(), it2) == 0) {
                fileContent << "color=\"red\"";
            }

        }
        fileContent << "];" << std::endl;
    }
    fileContent << "}" << std::endl;
    FileManager::saveSolution(fileName, fileContent.str());
}
