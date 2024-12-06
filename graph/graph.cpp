#include "graph.hpp"

graph::graph(std::vector<std::shared_ptr<node>> nodes, std::vector<std::shared_ptr<edge>> edges)
    : nodes(std::move(nodes)), edges(std::move(edges)) {
    if (this->nodes.empty()) {
        throw std::invalid_argument("Nodes vector cannot be empty!");
    }
    std::ranges::sort(nodes);
}

double graph::get_cost_between_nodes(const node &node1, const node &node2) {
    for(const edge* e : node1.get_edges()) {
        if (*e->get_target_node() == node2) {
            return e->get_weight();
        }
    }
    return std::numeric_limits<double>::infinity();
}

double graph::get_cost_of_sub_path(std::vector<node> subPath) {
    double cost = 0;
    for (int i = 0; i < subPath.size() - 1; i++) {
        cost += get_cost_between_nodes(subPath[i], subPath[i + 1]);
    }
    return cost;
}

double graph::get_cost_of_ham_path(std::vector<node> HamPath) {
    double cost = 0;
    for (int i = 0; i < HamPath.size(); i++) {
        cost += get_cost_between_nodes(HamPath[i], HamPath[(i + 1)%HamPath.size()]);
    }
    return cost;
}

const std::vector<std::shared_ptr<node>>& graph::get_nodes() const {
    return this->nodes;
}

const std::vector<std::shared_ptr<edge>>& graph::get_edges() const {
    return this->edges;
}

