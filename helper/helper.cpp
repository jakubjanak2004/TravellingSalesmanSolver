#include "helper.hpp"
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