#ifndef GRAPH_H
#define GRAPH_H

#include "node.hpp"
#include "edge.hpp"

#include <vector>


class graph {
public:
    graph(std::vector<std::shared_ptr<node>> nodes, std::vector<std::shared_ptr<edge>> edges);

    [[nodiscard]] static double get_cost_between_nodes(const node &node1, const node &node2);
    [[nodiscard]] static double get_cost_of_sub_path(std::vector<node> subPath);
    [[nodiscard]] static double get_cost_of_ham_path(std::vector<node> HamPath);

    [[nodiscard]] const std::vector<std::shared_ptr< node>>& get_nodes() const;
    [[nodiscard]] const std::vector<std::shared_ptr<edge>>& get_edges() const;

protected:
    std::vector<std::shared_ptr<node> > nodes;
    std::vector<std::shared_ptr<edge> > edges;
};


#endif //GRAPH_H
