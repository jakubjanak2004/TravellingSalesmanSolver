//
// Created by Jakub Janak on 9/14/24.
//

#include "../files/FileManager.h"
#include "../helper/Helper.h"
#include "TSInstance.h"
#include "Node.h"

#include <sstream>

TSInstance::TSInstance(std::vector<std::unique_ptr<Node> > nodes, std::vector<std::unique_ptr<Edge> > edges)
    : Graph(std::move(nodes), std::move(edges)),
      minCost(std::numeric_limits<double>::infinity()),
      startingNode(*this->nodes[0]) {
}

std::unique_ptr<TSInstance> TSInstance::createSyntheticInstance(const int numOfNodes) {
    std::vector<std::unique_ptr<Node> > nodes;
    std::vector<std::unique_ptr<Edge> > edges;
    nodes.reserve(numOfNodes);
    for (int i = 0; i < numOfNodes; i++) {
        nodes.emplace_back(std::make_unique<Node>(std::to_string(i)));
    }

    long counter = 0;
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes.size(); j++) {
            if (i < j) {
                auto edge1 = std::make_unique<Edge>(nodes[i].get(), nodes[j].get(), Helper::getRandomInteger(1, 10));
                nodes[i]->addEdge(edge1.get());
                auto edge2 = std::make_unique<Edge>(nodes[j].get(), nodes[i].get(), Helper::getRandomInteger(1, 10));
                nodes[j]->addEdge(edge2.get());
                edges.push_back(std::move(edge1));
                edges.push_back(std::move(edge2));
                counter++;
            }
        }
    }

    return std::make_unique<TSInstance>(std::move(nodes), std::move(edges));
}

std::vector<std::vector<Node> > TSInstance::solve(const std::string &args) {
    const auto start = std::chrono::high_resolution_clock::now();
    const std::vector visitedNodes = {this->startingNode};
    this->setMinCost(heuristicCombo());
    if (args == "p") {
        // safe threads for M2 max: <= 8
        startBranchParallel(visitedNodes, 0, this->startingNode, 10);
    } else {
        branch(visitedNodes, 0, this->startingNode);
    }
    const auto end = std::chrono::high_resolution_clock::now();
    this->elapsed = end - start;
    return this->bestHamiltonianPaths;
}

std::vector<std::vector<Node> > TSInstance::bruteForceSolve() const {
    std::vector<std::vector<Node> > allPerms;
    std::vector<Node *> rawPtrNodes;

    rawPtrNodes.reserve(this->nodes.size());
    for (const auto &node: this->nodes) {
        rawPtrNodes.push_back(node.get());
    }

    // Fix the first node
    const Node *firstNode = rawPtrNodes.front();
    std::vector<Node *> nextNodes(rawPtrNodes.begin() + 1, rawPtrNodes.end());

    // Generate permutations of the remaining nodes
    do {
        std::vector<Node> currentPerm;
        currentPerm.push_back(*firstNode); // Always start with the first node
        for (const auto &nodePtr: nextNodes) {
            currentPerm.push_back(*nodePtr);
        }
        allPerms.push_back(currentPerm); // Save the current permutation
    } while (std::next_permutation(nextNodes.begin(), nextNodes.end(), [](Node *a, Node *b) {
        return a->getName() < b->getName();
    }));

    double minCost = std::numeric_limits<double>::infinity();
    std::vector<std::vector<Node> > bestHamiltonianPathsBrute;
    for (const auto &perm: allPerms) {
        double cost = getCostOfHamPath(perm);
        if (cost < minCost) {
            minCost = cost;
            bestHamiltonianPathsBrute.clear();
            bestHamiltonianPathsBrute.push_back(perm);
        } else if (cost == minCost) {
            bestHamiltonianPathsBrute.push_back(perm);
        }
    }

    return bestHamiltonianPathsBrute;
}

void TSInstance::branch(std::vector<Node> visitedNodes, double cost, Node &currentNode) {
    for (const std::vector<Node *> neighbours = currentNode.getNeighbourNodes(); Node *neighbour: neighbours) {
        if (std::find(visitedNodes.begin(), visitedNodes.end(), *neighbour) != visitedNodes.end()) {
            continue;
        }
        std::vector<Node> branchVisNodes = visitedNodes;
        branchVisNodes.push_back(*neighbour);
        if (this->getLowerBound(branchVisNodes) <= this->minCost) {
            branch(branchVisNodes, cost + getCostBetweenNodes(currentNode, *neighbour), *neighbour);
        }
    }
    if (visitedNodes.size() == this->nodes.size()) {
        cost += getCostBetweenNodes(visitedNodes.back(), startingNode);
        if (cost < this->minCost) {
            this->setMinCost(cost);
            clearBestHams();
            addBestHamiltonian(visitedNodes);
        } else if (cost == this->minCost) {
            addBestHamiltonian(visitedNodes);
        }
    }
}

void TSInstance::startBranchParallel(const std::vector<Node> &visitedNodes, double cost, Node &currentNode,
                                     int numberOfThreads) {
    pool = std::make_unique<boost::asio::thread_pool>(numberOfThreads); // assign the thread pool
    post(*pool, [&] {
        branchParallel(visitedNodes, cost, currentNode); // start bb parallel
    });
    pool->join(); // join all threads in the thread pool
}

void TSInstance::branchParallel(std::vector<Node> visitedNodes, double cost, Node &currentNode) {
    Node *firstNeighbour = nullptr;
    std::vector<Node> firstBranchVisNodes;
    double firstSendCost = 0;

    for (const std::vector<Node *> neighbours = currentNode.getNeighbourNodes(); Node *neighbour: neighbours) {
        if (std::find(visitedNodes.begin(), visitedNodes.end(), *neighbour) != visitedNodes.end()) {
            continue;
        }
        std::vector<Node> branchVisNodes = visitedNodes;
        branchVisNodes.push_back(*neighbour);
        // I need to do this dept-first
        if (this->getLowerBound(branchVisNodes) <= getMinCost()) {
            double sendCost = cost + getCostBetweenNodes(currentNode, *neighbour);

            // For the first neighbor, store its data to run it immediately after posting others
            if (!firstNeighbour) {
                firstNeighbour = neighbour;
                firstBranchVisNodes = branchVisNodes;
                firstSendCost = sendCost;
            } else {
                // Post all other neighbors to the thread pool (parallel execution)
                post(*pool, [this, branchVisNodes, sendCost, neighbour] {
                    branchParallel(branchVisNodes, sendCost, *neighbour);
                });
            }
        }
    }

    // After all neighbors are posted to the thread pool, handle the first neighbor immediately
    if (firstNeighbour) {
        branchParallel(firstBranchVisNodes, firstSendCost, *firstNeighbour);
    }

    if (visitedNodes.size() == nodes.size()) {
        cost += getCostBetweenNodes(visitedNodes.back(), startingNode);
        if (cost < getMinCost()) {
            setMinCost(cost);
            clearBestHams();
            addBestHamiltonian(visitedNodes);
        } else if (cost == getMinCost()) {
            addBestHamiltonian(visitedNodes);
        }
    }
}

double TSInstance::getLowerBound(std::vector<Node> subPath) const {
    double cost = getCostOfSubPath(subPath);

    for (auto &node: this->nodes) {
        if (std::find(subPath.begin(), subPath.end() - 1, *node) == subPath.end() - 1) {
            std::vector<Edge *> edges = node->getEdges();
            if (edges.empty()) {
                continue;
            }
            const Edge *edge = *edges.begin();
            cost += edge->getWeight();
        }
    }
    return cost;
}

void TSInstance::nearest_neighbour(std::vector<Node>& greedyPath) const {
    Node node = this->startingNode;
    do {
        greedyPath.push_back(node);
        std::vector<Edge *> edgesOfNode = greedyPath.back().getEdges();
        for (const Edge *edge: edgesOfNode) {
            if (auto it = std::find(greedyPath.begin(), greedyPath.end(), *edge->getTargetNode());
                it == greedyPath.end()) {
                node = *edge->getTargetNode();
                break;
            }
        }
    } while (greedyPath.size() < this->nodes.size());
}

double TSInstance::two_opt(std::vector<Node> greedyPath) {
    double minCost = getCostOfHamPath(greedyPath);
    for (int i = 0; i < greedyPath.size(); i++) {
        for (int j = 0; j < greedyPath.size(); j++) {
            if (i == j) continue;
            std::swap(greedyPath[i], greedyPath[j]);
            if (const double cost = getCostOfHamPath(greedyPath); cost < minCost) {
                minCost = cost;
            } else {
                std::swap(greedyPath[i], greedyPath[j]);
            }
        }
    }

    // return the Cost of the best Hamiltonian Path found
    return minCost;
}

double TSInstance::heuristicCombo() {
    std::vector<Node> greedyPath;

    // Nearest Neighbor
    nearest_neighbour(greedyPath);

    // 2-opt
    return two_opt(greedyPath);
}

double TSInstance::getMinCost() {
    std::lock_guard lock(m_1);
    return this->minCost;
}

void TSInstance::setMinCost(const double minCost) {
    std::lock_guard lock(m_1);
    this->minCost = minCost;
}

bool TSInstance::isSolved() const {
    return !this->bestHamiltonianPaths.empty();
}

void TSInstance::clearBestHams() {
    std::lock_guard lock(m_1);
    this->bestHamiltonianPaths.clear();
}

void TSInstance::addBestHamiltonian(const std::vector<Node> &path) {
    std::lock_guard lock(m_1);
    this->bestHamiltonianPaths.push_back(path);
}

void TSInstance::printStatistics() const {
    std::cout << std::endl;
    std::cout << this->toString() << std::endl;

    if (this->bestHamiltonianPaths.empty()) {
        std::cout << "NO RESULT WAS FOUND" << std::endl;
        return;
    }

    std::cout << "Solution set size: " << this->bestHamiltonianPaths.size() << std::endl;
    std::cout << "The optimal path length: " << this->minCost << std::endl;
    std::cout << "Calculation took: " << elapsed.count() / 1000000 << " ms (" << elapsed.count() << "ns)" << std::endl;

    std::cout << "First hamiltonian: ";
    for (const Node &node: this->bestHamiltonianPaths.front()) {
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
        if (!this->bestHamiltonianPaths.empty()) {
            auto it1 = std::find(this->bestHamiltonianPaths[0].begin(), this->bestHamiltonianPaths[0].end(),
                                 *edge->getSourceNode());
            auto it2 = std::find(this->bestHamiltonianPaths[0].begin(), this->bestHamiltonianPaths[0].end(),
                                 *edge->getTargetNode());
            auto dis1 = std::distance(this->bestHamiltonianPaths[0].begin(), it2);
            auto dis2 = std::distance(this->bestHamiltonianPaths[0].begin(), it1);
            if (it1 != this->bestHamiltonianPaths[0].end() && it2 != this->bestHamiltonianPaths[0].end()) {
                if (dis1 - dis2 == 1) {
                    fileContent << "color=\"red\"";
                }
                if (std::distance(this->bestHamiltonianPaths[0].begin(), it1) == this->bestHamiltonianPaths[0].size() -
                    1 &&
                    std::distance(this->bestHamiltonianPaths[0].begin(), it2) == 0) {
                    fileContent << "color=\"red\"";
                }
            }
        }

        fileContent << "];" << std::endl;
    }
    fileContent << "}" << std::endl;
    FileManager::saveSolution(fileName, fileContent.str());
}

std::string TSInstance::toString() const {
    std::ostringstream oss;
    oss << "Travelling Salesman Instance with: " << this->nodes.size() << " nodes";
    return oss.str();
}
