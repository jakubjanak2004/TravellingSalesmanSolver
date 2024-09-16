#include "controller/Controller.h"

#include <iostream>
#include <random>

int main() {
    Controller controller = Controller();
    controller.run();

    // testing the solver on a generated graph
    // test_BB();

    // Initial estimate:
    // I may be implementing 2Opt with nearest neighbour search as the minLength estimate
    // especially for the parallel version of the branch and bound

    // better bound:
    // I can be implementing the lower bound that checks
    // cost of the subpath +
    // weight of the minimal spanning tree of unvisited nodes +
    // shortest edges from the home node and last node to the unvisited nodes (cannot be connected to the same node)
}