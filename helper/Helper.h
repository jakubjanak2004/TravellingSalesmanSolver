#ifndef HELPER_H
#define HELPER_H

#include "../graph/Node.h"
#include <set>

class Helper {
public:
    static int get_random_integer(int from, int to);
    static std::set<std::vector<Node> > convert_to_node_set(const std::vector<std::vector<Node> > &paths);
};



#endif //HELPER_H
