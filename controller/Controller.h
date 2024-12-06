#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../graph/TSInstance.h"
#include <boost/program_options.hpp>


class Controller {
    std::deque<std::unique_ptr<TSInstance>> unsolvedInstances;
    boost::program_options::options_description desc = {"Arguments"};

    static void print_header();

    void load_instance(const std::string& file_name);

    void auto_load_instances();

    void create_synthetic_instance(int num_of_nodes);

    void solve(int num_of_threads = 1); // not multithreaded by default

    void heuristic_combo();

public:
    Controller();

    int run(int argc, char *argv[]);

};


#endif //CONTROLLER_H
