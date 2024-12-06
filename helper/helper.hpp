#ifndef HELPER_H
#define HELPER_H

#include "../graph/Node.hpp"
#include <set>

class helper {
public:
    static int get_random_integer(int from, int to);
    static std::set<std::vector<node> > convert_to_node_set(const std::vector<std::vector<node> > &paths);
};



#endif //HELPER_H
