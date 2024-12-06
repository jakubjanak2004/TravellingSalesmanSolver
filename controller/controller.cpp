#include "controller.hpp"
#include "../helper/helper.hpp"
#include "../files/file_manager.hpp"

#include <iostream>
#include <random>
#include <filesystem>
#include <fstream>
#include <string>

controller::controller() {
    desc.add_options()
            ("help,h", "Print help message")
            ("load-instances,l", boost::program_options::value<std::string>(), "Specify load instances file")
            ("auto-load-instances,a", "Auto load instances from files/instances folder")
            ("create-synthetic-instance,c", boost::program_options::value<int>(),
             "Create synthetic instance (fully connected graph) with n vertices")
            ("solve,s", "Solve the instances in queue")
            ("solve-parallel,p", boost::program_options::value<int>(),
             "Parallel solve the instances in queue, with number of threads")
            ("heuristic-combo,e", "Use nearest neighbour + 2Opt to approximate the best path");
}

void controller::print_header() {
    std::cout << "\033[1;34m";
    std::cout << "                                               " << std::endl;
    std::cout << R"(  TTTTTTTT\     $$$$$$$\     $$$$$$$\   )" << std::endl;
    std::cout << "     TT  __|    $$  ____|    $$  ____|     " << std::endl;
    std::cout << "     TT |       $$$$$$$\\     $$$$$$$\\    " << std::endl;
    std::cout << "     TT |            $$ |         $$ |     " << std::endl;
    std::cout << "     TT |       $$$$$$$ |    $$$$$$$ |     " << std::endl;
    std::cout << R"(     \__|       \_______|    \_______|  )" << std::endl;
    std::cout << std::endl;
    std::cout << "\033[0m";
}

int controller::run(const int argc, char *argv[]) {
    // print header every time
    print_header();

    try {
        boost::program_options::variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        // Print help message
        if (argc == 1 || vm.contains("help")) {
            std::cout << desc << std::endl;
            return 0;
        }

        // load / create instances
        if (vm.contains("load-instances")) {
            const std::string path = vm["load-instances"].as<std::string>();
            load_instance(path);
        }

        if (vm.contains("auto-load-instances")) {
            auto_load_instances();
        }

        if (vm.contains("create-synthetic-instance")) {
            const int num_of_nodes = vm["create-synthetic-instance"].as<int>();
            create_synthetic_instance(num_of_nodes);
        }

        // solving
        if (vm.contains("solve")) {
            solve();
        }

        if (vm.contains("solve-parallel")) {
            const int num_of_threads = vm["solve-parallel"].as<int>();
            if (num_of_threads <= 0) {
                std::cerr << "Number of threads must be an integer >= 1" << std::endl;
                return 1;
            }
            if (num_of_threads == 1) {
                std::cerr << "For single threaded solving call --solve" << std::endl;
            }
            solve(num_of_threads);
        }

        // approximation
        if (vm.contains("heuristic-combo")) {
            heuristic_combo();
        }
        return 0;
    } catch (const boost::program_options::error &ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        std::cerr << desc << "\n";
        return 1;
    }
}

void controller::load_instance(const std::string &file_name) {
    std::unique_ptr<ts_instance> tsInstance = file_manager::read_dot_file(
        file_manager::INSTANCES_PATH + "/" + file_name);
    if (tsInstance == nullptr) {
        return;
    }
    std::cout << "loaded: " << file_name << std::endl;
    this->unsolvedInstances.push_back(std::move(tsInstance));
}

void controller::auto_load_instances() {
    std::cout << "Loading all instances from " << file_manager::INSTANCES_PATH << " automatically" << std::endl;
    for (const auto &entry: file_manager::get_dot_instances(file_manager::INSTANCES_PATH)) {
        std::unique_ptr<ts_instance> tsInstance = file_manager::read_dot_file(entry.path().string());
        this->unsolvedInstances.push_back(std::move(tsInstance));
    }
}

void controller::create_synthetic_instance(const int num_of_nodes) {
    this->unsolvedInstances.push_back(helper::create_synthetic_instance(num_of_nodes));
    std::cout << "created synthetic instance with: " << num_of_nodes << " nodes" << std::endl;
}

void controller::solve(const int num_of_threads) {
    if (this->unsolvedInstances.empty()) {
        std::cout << "Nothing to solve!" << std::endl;
        return;
    }
    while (!this->unsolvedInstances.empty()) {
        std::cout << "Solving..." << std::endl;
        auto &instance = this->unsolvedInstances.front();
        instance->solve(num_of_threads);
        instance->print_statistics();
        if (!instance->is_solved()) {
            this->unsolvedInstances.pop_front();
            continue;
        }
        std::string userInput;
        std::cout << "Save the result graph[y for yes]: ";
        std::getline(std::cin, userInput);
        if (userInput.find('y') != std::string::npos) {
            std::cout << "Name of the file: ";
            std::getline(std::cin, userInput);
            instance->save(userInput);
        }
        this->unsolvedInstances.pop_front();
    }
}

void controller::heuristic_combo() {
    if (this->unsolvedInstances.empty()) {
        std::cout << "Nothing to approximate!" << std::endl;
        return;
    }
    while (!this->unsolvedInstances.empty()) {
        auto &instance = this->unsolvedInstances.front();
        const double result = instance->heuristic_combo();
        std::cout << std::endl << instance->to_string() << std::endl;
        std::cout << "Heuristic Approximation: " << result << std::endl;
        this->unsolvedInstances.pop_front();
    }
}
