#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../graph/ts_instance.hpp"
#include "controller_strategy/controller_strategy.hpp"
#include <boost/program_options.hpp>

class controller {
    std::deque<std::unique_ptr<ts_instance> > unsolvedInstances;
    boost::program_options::options_description desc = {"Arguments"};
    strategy_context cont;

    static void print_header();

public:
    void load_instance(const std::string &file_name);

    void auto_load_instances();

    void create_synthetic_instance(int num_of_nodes);

    // not multithreaded by default
    void solve(int num_of_threads = 1);

    void heuristic_combo();

    controller();

    int run(int argc, char *argv[]);

    boost::program_options::options_description get_desc();
};


#endif
