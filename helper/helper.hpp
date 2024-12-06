#ifndef HELPER_H
#define HELPER_H

#include "../graph/node.hpp"
#include "../graph/ts_instance.hpp"
#include <set>

namespace helper {
    int get_random_integer(int from, int to);
    std::set<std::vector<node> > convert_to_node_set(const std::vector<std::vector<node> > &paths);
    std::unique_ptr<ts_instance> create_synthetic_instance(int numOfNodes);
}



#endif
