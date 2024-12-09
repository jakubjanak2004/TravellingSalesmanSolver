#include "../files/file_manager.hpp"
#include "../helper/helper.hpp"
#include "ts_instance.hpp"
#include "node.hpp"

#include <sstream>

ts_instance::ts_instance(std::vector<std::shared_ptr<node> > nodes, std::vector<std::shared_ptr<edge> > edges)
    : graph(std::move(nodes), std::move(edges)),
      minCost(std::numeric_limits<double>::infinity()),
      startingNode(*this->nodes[0]) {
}

std::vector<std::vector<node> > ts_instance::solve(const int num_of_threads) {
    const auto start = std::chrono::high_resolution_clock::now();
    const std::vector visitedNodes = {this->startingNode};
    this->set_min_cost(heuristic_combo());
    if (num_of_threads > 1) {
        start_branch_parallel(visitedNodes, 0, this->startingNode, num_of_threads);
    } else {
        branch(visitedNodes, 0, this->startingNode);
    }
    const auto end = std::chrono::high_resolution_clock::now();
    this->elapsed = end - start;
    return this->bestHamiltonianPaths;
}

std::vector<std::vector<node> > ts_instance::brute_force_solve() const {
    std::vector<std::vector<node> > allPerms;
    std::vector<node *> rawPtrNodes;

    rawPtrNodes.reserve(this->nodes.size());
    for (const auto &node: this->nodes) {
        rawPtrNodes.push_back(node.get());
    }

    // Fix the first node
    const node *firstNode = rawPtrNodes.front();
    std::vector<node *> nextNodes(rawPtrNodes.begin() + 1, rawPtrNodes.end());

    // Generate permutations of the remaining nodes
    do {
        std::vector<node> currentPerm;
        currentPerm.push_back(*firstNode); // Always start with the first node
        for (const auto &nodePtr: nextNodes) {
            currentPerm.push_back(*nodePtr);
        }
        allPerms.push_back(currentPerm); // Save the current permutation
    } while (std::next_permutation(nextNodes.begin(), nextNodes.end(), [](node *a, node *b) {
        return a->get_name() < b->get_name();
    }));

    double minCost = std::numeric_limits<double>::infinity();
    std::vector<std::vector<node> > bestHamiltonianPathsBrute;
    for (const auto &perm: allPerms) {
        double cost = get_cost_of_ham_path(perm);
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

void ts_instance::branch(std::vector<node> visitedNodes, double cost, const node &currentNode) {
    for (const std::vector<node *> neighbours = currentNode.get_neighbour_nodes(); const node *neighbour: neighbours) {
        if (std::ranges::find(visitedNodes, *neighbour) != visitedNodes.end()) {
            continue;
        }
        std::vector<node> branchVisNodes = visitedNodes;
        branchVisNodes.push_back(*neighbour);
        if (this->get_lower_bound(branchVisNodes) <= this->minCost) {
            branch(branchVisNodes, cost + get_cost_between_nodes(currentNode, *neighbour), *neighbour);
        }
    }
    if (visitedNodes.size() == this->nodes.size()) {
        cost += get_cost_between_nodes(visitedNodes.back(), startingNode);
        if (cost < this->minCost) {
            this->set_min_cost(cost);
            clear_best_hams();
            add_best_hamiltonian(visitedNodes);
        } else if (cost == this->minCost) {
            add_best_hamiltonian(visitedNodes);
        }
    }
}

void ts_instance::start_branch_parallel(const std::vector<node> &visitedNodes, double cost, node &currentNode,
                                     int numberOfThreads) {
    pool = std::make_unique<boost::asio::thread_pool>(numberOfThreads); // assign the thread pool
    post(*pool, [&] {
        branch_parallel(visitedNodes, cost, currentNode); // start bb parallel
    });
    pool->join(); // join all threads in the thread pool
}

void ts_instance::branch_parallel(std::vector<node> visitedNodes, double cost, const node &currentNode) {
    node *firstNeighbour = nullptr;
    std::vector<node> firstBranchVisNodes;
    double firstSendCost = 0;

    for (const std::vector<node *> neighbours = currentNode.get_neighbour_nodes(); node *neighbour: neighbours) {
        if (std::find(visitedNodes.begin(), visitedNodes.end(), *neighbour) != visitedNodes.end()) {
            continue;
        }
        std::vector<node> branchVisNodes = visitedNodes;
        branchVisNodes.push_back(*neighbour);
        // I need to do this dept-first
        if (this->get_lower_bound(branchVisNodes) <= get_min_cost()) {
            double sendCost = cost + get_cost_between_nodes(currentNode, *neighbour);

            // For the first neighbor, store its data to run it immediately after posting others
            if (!firstNeighbour) {
                firstNeighbour = neighbour;
                firstBranchVisNodes = branchVisNodes;
                firstSendCost = sendCost;
            } else {
                // Post all other neighbors to the thread pool (parallel execution)
                post(*pool, [this, branchVisNodes, sendCost, neighbour] {
                    branch_parallel(branchVisNodes, sendCost, *neighbour);
                });
            }
        }
    }

    // After all, neighbors are posted to the thread pool, handle the first neighbor immediately
    if (firstNeighbour) {
        branch_parallel(firstBranchVisNodes, firstSendCost, *firstNeighbour);
    }

    if (visitedNodes.size() == nodes.size()) {
        std::lock_guard lock(m_1);
        cost += get_cost_between_nodes(visitedNodes.back(), startingNode);
        if (cost < get_min_cost()) {
            set_min_cost(cost);
            clear_best_hams();
            add_best_hamiltonian(visitedNodes);
        } else if (cost == get_min_cost()) {
            add_best_hamiltonian(visitedNodes);
        }
    }
}

double ts_instance::get_lower_bound(std::vector<node> subPath) const {
    double cost = get_cost_of_sub_path(subPath);

    for (auto &node: this->nodes) {
        if (std::find(subPath.begin(), subPath.end() - 1, *node) == subPath.end() - 1) {
            std::vector<edge *> edges = node->get_edges();
            if (edges.empty()) {
                continue;
            }
            const edge *e = *edges.begin();
            cost += e->get_weight();
        }
    }
    return cost;
}

void ts_instance::nearest_neighbour(std::vector<node>& greedyPath) const {
    node node = this->startingNode;
    do {
        greedyPath.push_back(node);
        std::vector<edge *> edges_of_node = greedyPath.back().get_edges();
        for (const edge *edge: edges_of_node) {
            if (auto it = std::ranges::find(greedyPath, *edge->get_target_node());
                it == greedyPath.end()) {
                node = *edge->get_target_node();
                break;
            }
        }
    } while (greedyPath.size() < this->nodes.size());
}

double ts_instance::two_opt(std::vector<node> greedyPath) {
    double minCost = get_cost_of_ham_path(greedyPath);
    for (int i = 0; i < greedyPath.size(); i++) {
        for (int j = 0; j < greedyPath.size(); j++) {
            if (i == j) continue;
            std::swap(greedyPath[i], greedyPath[j]);
            if (const double cost = get_cost_of_ham_path(greedyPath); cost < minCost) {
                minCost = cost;
            } else {
                std::swap(greedyPath[i], greedyPath[j]);
            }
        }
    }

    // return the Cost of the best Hamiltonian Path found
    return minCost;
}

double ts_instance::heuristic_combo() const {
    std::vector<node> greedyPath;

    // Nearest Neighbor
    nearest_neighbour(greedyPath);

    // 2-opt
    return two_opt(greedyPath);
}

double ts_instance::get_min_cost() {
    std::lock_guard lock(m_2);
    return this->minCost;
}

void ts_instance::set_min_cost(const double minCost) {
    this->minCost = minCost;
}

bool ts_instance::is_solved() const {
    return !this->bestHamiltonianPaths.empty();
}

void ts_instance::clear_best_hams() {
    this->bestHamiltonianPaths.clear();
}

void ts_instance::add_best_hamiltonian(const std::vector<node> &path) {
    this->bestHamiltonianPaths.push_back(path);
}

void ts_instance::print_statistics() const {
    std::cout << std::endl;
    std::cout << this->to_string() << std::endl;

    if (this->bestHamiltonianPaths.empty()) {
        std::cout << "NO RESULT WAS FOUND" << std::endl;
        return;
    }

    std::cout << "Solution set size: " << this->bestHamiltonianPaths.size() << std::endl;
    std::cout << "The optimal path length: " << this->minCost << std::endl;
    std::cout << "Calculation took: " << elapsed.count() / 1000000 << " ms (" << elapsed.count() << "ns)" << std::endl;

    std::cout << "First hamiltonian: ";
    for (const node &node: this->bestHamiltonianPaths.front()) {
        std::cout << node.to_string() << " ";
    }
    std::cout << std::endl;
}

void ts_instance::save(const std::string &fileName) const {
    std::ostringstream fileContent;
    fileContent << "digraph G {" << std::endl;
    for (auto &node: this->nodes) {
        fileContent << node->to_string() << ";" << std::endl;
    }
    for (auto &edge: this->edges) {
        std::ostringstream weight;
        weight << std::defaultfloat << edge->get_weight();
        fileContent << edge->get_source_node()->to_string() << " -> " << edge->get_target_node()->to_string()
                << "[label=\"" << weight.str() << "\" weight=\"" << weight.str() << "\"";
        if (!this->bestHamiltonianPaths.empty()) {
            auto it1 = std::ranges::find(this->bestHamiltonianPaths[0],
                                         *edge->get_source_node());
            auto it2 = std::ranges::find(this->bestHamiltonianPaths[0],
                                         *edge->get_target_node());
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
    file_manager::save_solution(fileName, fileContent.str());
}

std::string ts_instance::to_string() const {
    std::ostringstream oss;
    oss << "Travelling Salesman Instance with: " << this->nodes.size() << " nodes";
    return oss.str();
}

void ts_instance::reset_solution() {
    bestHamiltonianPaths.clear();
    minCost = std::numeric_limits<double>::infinity();
}
