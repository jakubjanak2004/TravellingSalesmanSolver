//
// Created by Jakub Janak on 9/15/24.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../graph/TSInstance.h"
#include <boost/program_options.hpp>


class Controller {
    std::deque<std::unique_ptr<TSInstance>> unsolvedInstances;
    boost::program_options::options_description desc = {"Arguments"};

public:
    Controller();

    static void printHeader();

    int run(int argc, char *argv[]);

    void loadInstance(const std::string& file_name);

    void autoLoadInstances();

    void createSyntheticInstance(int num_of_nodes);

    void solve(const std::string& args);

    void heuristicCombo();
};


#endif //CONTROLLER_H
