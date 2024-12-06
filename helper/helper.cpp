#include "helper.hpp"
#include "../graph/ts_instance.hpp"
#include <random>

int helper::get_random_integer(const int from, const int to) {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution intDist(from, to);

    return intDist(rng);
}

std::set<std::vector<node> > helper::convert_to_node_set(const std::vector<std::vector<node> > &paths) {
    std::set<std::vector<node> > nodeSet;
    for (const auto &path: paths) {
        nodeSet.insert(path);
    }
    return nodeSet;
}

std::unique_ptr<ts_instance> helper::create_synthetic_instance(const int numOfNodes) {
    std::vector<std::shared_ptr<node> > nodes;
    std::vector<std::shared_ptr<edge> > edges;
    nodes.reserve(numOfNodes);
    for (int i = 0; i < numOfNodes; i++) {
        nodes.emplace_back(std::make_unique<node>(std::to_string(i)));
    }

    long counter = 0;
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes.size(); j++) {
            if (i < j) {
                auto edge1 = std::make_unique<edge>(nodes[i].get(), nodes[j].get(), helper::get_random_integer(1, 10));
                nodes[i]->add_edge(edge1.get());
                auto edge2 = std::make_unique<edge>(nodes[j].get(), nodes[i].get(), helper::get_random_integer(1, 10));
                nodes[j]->add_edge(edge2.get());
                edges.push_back(std::move(edge1));
                edges.push_back(std::move(edge2));
                counter++;
            }
        }
    }

    return std::make_unique<ts_instance>(std::move(nodes), std::move(edges));
}