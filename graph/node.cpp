#include "Node.hpp"
#include "Edge.hpp"

node::node(std::string name) {
    this->name = std::move(name);
}

void node::add_edge(edge *e) {
    int addingIndex = 0;
    for (const auto &loopEdge: this->edges) {
        if (loopEdge->get_weight() < e->get_weight()) {
            addingIndex++;
        }
    }
    this->edges.insert(edges.begin() + addingIndex, e);
}

std::vector<node *> node::get_neighbour_nodes() const {
    std::vector<node *> neighbours;
    neighbours.reserve(this->edges.size());
    for (const edge *edge: this->edges) {
        neighbours.push_back(edge->get_target_node());
    }
    return neighbours;
}

bool node::operator<(const node &other) const {
    return this->name < other.name;
}

bool node::operator>(const node &other) const {
    return this->name > other.name;
}

bool node::operator==(const node &other) const {
    return this->name == other.name;
}

bool node::operator!=(const node &other) const {
    return this->name != other.name;
}

std::string node::to_string() const {
    return this->name;
}

std::vector<edge *> node::get_edges() const {
    return this->edges;
}

std::string node::get_name() {
    return this->name;
}
