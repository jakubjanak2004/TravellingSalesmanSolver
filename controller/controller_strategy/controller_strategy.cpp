#include "controller_strategy.hpp"
#include "../../controller/controller.hpp"

strategy_context::strategy_context(controller* contr): contr(contr) {
    controller_strategies.push_back(std::make_unique<help_strategy>(contr));
    controller_strategies.push_back(std::make_unique<load_instances_strategy>(contr));
    controller_strategies.push_back(std::make_unique<auto_load_instances_strategy>(contr));
    controller_strategies.push_back(std::make_unique<create_synthetic_instances_strategy>(contr));
    controller_strategies.push_back(std::make_unique<solve_strategy>(contr));
    controller_strategies.push_back(std::make_unique<solve_parallel_strategy>(contr));
    controller_strategies.push_back(std::make_unique<heuristic_strategy>(contr));
}

void strategy_context::run_strategy(const int argc, const boost::program_options::variables_map& vm) {
    for (auto& strategy : controller_strategies) {
        strategy->response_to_commit(argc, vm);
    }
}


void help_strategy::response_to_commit(const int argc, boost::program_options::variables_map vm) {
    if (argc == 1 || vm.contains("help")) {
        std::cout << contr->get_desc() << std::endl;
    }
}

void load_instances_strategy::response_to_commit(const int argc, boost::program_options::variables_map vm) {
    if (vm.contains("load-instances")) {
        const std::string path = vm["load-instances"].as<std::string>();
        contr->load_instance(path);
    }
}

void auto_load_instances_strategy::response_to_commit(const int argc, boost::program_options::variables_map vm)  {
    if (vm.contains("auto-load-instances")) {
        contr->auto_load_instances();
    }
}

void create_synthetic_instances_strategy::response_to_commit(const int argc, boost::program_options::variables_map vm) {
    if (vm.contains("create-synthetic-instance")) {
        const int num_of_nodes = vm["create-synthetic-instance"].as<int>();
        contr->create_synthetic_instance(num_of_nodes);
    }
}

void solve_strategy::response_to_commit(const int argc, boost::program_options::variables_map vm) {
    if (vm.contains("solve")) {
        contr->solve();
    }
}

void solve_parallel_strategy::response_to_commit(const int argc, boost::program_options::variables_map vm) {
    if (vm.contains("solve-parallel")) {
        const int num_of_threads = vm["solve-parallel"].as<int>();
        if (num_of_threads <= 0) {
            std::cerr << "Number of threads must be an integer >= 1" << std::endl;
            return;
        }
        if (num_of_threads == 1) {
            std::cerr << "For single threaded solving call --solve" << std::endl;
        }
        contr->solve(num_of_threads);
    }
}

void heuristic_strategy::response_to_commit(const int argc, boost::program_options::variables_map vm) {
    if (vm.contains("heuristic-combo")) {
        contr->heuristic_combo();
    }
}
