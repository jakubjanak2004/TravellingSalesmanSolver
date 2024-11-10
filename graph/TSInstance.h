//
// Created by Jakub Janak on 9/14/24.
//

#ifndef TSINSTANCE_H
#define TSINSTANCE_H

#include "Graph.h"

#include <boost/asio.hpp>
#include <thread>


class TSInstance : public Graph {
    std::mutex m_1; // mutex for thread safety of minCost
    std::unique_ptr<boost::asio::thread_pool> pool;
    double minCost; // thread save minimal cost variable
    Node startingNode;
    std::vector<Node> nodesExplored;
    std::vector<std::vector<Node> > bestHamiltonianPaths;
    std::chrono::duration<long long, std::ratio<1, 1000000000> > elapsed{};

public:
    TSInstance(std::vector<std::shared_ptr<Node> > nodes, std::vector<std::shared_ptr<Edge> > edges);

    static std::unique_ptr<TSInstance> create_synthetic_instance(int numOfNodes);

    std::vector<std::vector<Node> > solve(int num_of_threads = 1); // not multithreaded by default

    void branch(std::vector<Node> visitedNodes, double cost, Node &currentNode);

    void start_branch_parallel(const std::vector<Node> &visitedNodes, double cost, Node &currentNode, int numberOfThreads);

    void branch_parallel(std::vector<Node> visitedNodes, double cost, Node &currentNode);

    [[nodiscard]] std::vector<std::vector<Node>> brute_force_solve() const;

    [[nodiscard]] double get_lower_bound(std::vector<Node> subPath) const;

    void nearest_neighbour(std::vector<Node>& greedyPath) const;

    double two_opt(std::vector<Node> greedyPath);

    [[nodiscard]] double heuristic_combo();

    [[nodiscard]] double get_min_cost();

    [[nodiscard]] bool is_solved() const;

    void set_min_cost(double minCost);

    void clear_best_hams();

    void add_best_hamiltonian(const std::vector<Node> &path);

    void print_statistics() const;

    void save(const std::string &fileName) const;

    [[nodiscard]] std::string to_string() const;
};


#endif //TSINSTANCE_H
