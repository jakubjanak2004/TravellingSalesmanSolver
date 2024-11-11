//
// Created by Jakub Janak on 9/19/24.
//

#include "Helper.h"
#include <random>

int Helper::get_random_integer(const int from, const int to) {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution intDist(from, to);

    return intDist(rng);
}

std::set<std::vector<Node> > Helper::convert_to_node_set(const std::vector<std::vector<Node> > &paths) {
    std::set<std::vector<Node> > nodeSet;
    for (const auto &path: paths) {
        nodeSet.insert(path);
    }
    return nodeSet;
}