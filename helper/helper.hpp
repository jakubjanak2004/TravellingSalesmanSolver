#ifndef HELPER_H
#define HELPER_H

#include "../graph/Node.hpp"
#include "../graph/ts_instance.hpp"
#include <set>

class helper {
public:
    static int get_random_integer(int from, int to);
    static std::set<std::vector<node> > convert_to_node_set(const std::vector<std::vector<node> > &paths);
    static std::unique_ptr<ts_instance> create_synthetic_instance(int numOfNodes);
};



#endif //HELPER_H
