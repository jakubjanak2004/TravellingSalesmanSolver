#include "Graph.hpp"

Graph::Graph(std::vector<std::shared_ptr<Node>> nodes, std::vector<std::shared_ptr<Edge>> edges)
    : nodes(std::move(nodes)), edges(std::move(edges)) {
    if (this->nodes.empty()) {
        throw std::invalid_argument("Nodes vector cannot be empty!");
    }
    std::sort(nodes.begin(), nodes.end());
}

double Graph::get_cost_between_nodes(Node &node1, const Node &node2) {
    for(const Edge* edge : node1.get_edges()) {
        if (*edge->get_target_node() == node2) {
            return edge->get_weight();
        }
    }
    return std::numeric_limits<double>::infinity();
}

double Graph::get_cost_of_sub_path(std::vector<Node> subPath) {
    double cost = 0;
    for (int i = 0; i < subPath.size() - 1; i++) {
        cost += get_cost_between_nodes(subPath[i], subPath[i + 1]);
    }
    return cost;
}

double Graph::get_cost_of_ham_path(std::vector<Node> HamPath) {
    double cost = 0;
    for (int i = 0; i < HamPath.size(); i++) {
        cost += get_cost_between_nodes(HamPath[i], HamPath[(i + 1)%HamPath.size()]);
    }
    return cost;
}

const std::vector<std::shared_ptr<Node>>& Graph::get_nodes() const {
    return this->nodes;
}

const std::vector<std::shared_ptr<Edge>>& Graph::get_edges() const {
    return this->edges;
}

