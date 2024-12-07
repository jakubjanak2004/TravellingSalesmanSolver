#ifndef TSINSTANCE_H
#define TSINSTANCE_H

#include "graph.hpp"

#include <boost/asio.hpp>
#include <thread>


class ts_instance : public graph {
    std::mutex m_1; // mutex for thread safety of minCost
    std::unique_ptr<boost::asio::thread_pool> pool;
    double minCost; // thread save minimal cost variable
    node startingNode;
    std::vector<node> nodesExplored;
    std::vector<std::vector<node> > bestHamiltonianPaths;
    std::chrono::duration<long long, std::ratio<1, 1000000000> > elapsed{};

    void branch(std::vector<node> visitedNodes, double cost, const node &currentNode);

    void start_branch_parallel(const std::vector<node> &visitedNodes, double cost, node &currentNode, int numberOfThreads);

    void branch_parallel(std::vector<node> visitedNodes, double cost, const node &currentNode);

    [[nodiscard]] double get_lower_bound(std::vector<node> subPath) const;

    void nearest_neighbour(std::vector<node>& greedyPath) const;

    static double two_opt(std::vector<node> greedyPath);

    [[nodiscard]] double get_min_cost();

    void set_min_cost(double minCost);

    void clear_best_hams();

    void add_best_hamiltonian(const std::vector<node> &path);

public:
    ts_instance(std::vector<std::shared_ptr<node> > nodes, std::vector<std::shared_ptr<edge> > edges);

    std::vector<std::vector<node> > solve(int num_of_threads = 1);

    [[nodiscard]] std::vector<std::vector<node>> brute_force_solve() const;

    [[nodiscard]] double heuristic_combo() const;

    [[nodiscard]] bool is_solved() const;

    void print_statistics() const;

    void save(const std::string &fileName) const;

    [[nodiscard]] std::string to_string() const;

    void reset_solution();
};


#endif
