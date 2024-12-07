#include "../graph/ts_instance.hpp"
#include "../helper/helper.hpp"

#include <fstream>
#include <iostream>

const std::string STATISTICS_FOLDER = "../files/data";
std::vector<std::string> data_to_csv = {};

void write_to_csv(const std::vector<std::string> &data, const std::string &filename = "output.csv") {
    if (std::ofstream file(STATISTICS_FOLDER + "/" + filename); file.is_open()) {
        for (const auto &element: data) {
            file << element << "\n"; // Write each element to a new line
        }
        file.close();
    } else {
        std::cerr << "Failed to open the file." << std::endl;
    }
    data_to_csv.clear();
}

void set_stats_up() {
    // create STATISTICS FOLDER if note exists
    if (!std::filesystem::exists(STATISTICS_FOLDER)) {
        if (std::filesystem::create_directory(STATISTICS_FOLDER)) {
            std::cout << "Created statistics directory: " << STATISTICS_FOLDER << std::endl;
        } else {
            std::cout << "Error creating statistics directory: " << STATISTICS_FOLDER << std::endl;
        }
    }
}

void compare_brute_force_solve() {
    int max_instance_size = 9;
    int data_per_instance_size = 20;

    for (int i = 3; i <= max_instance_size; i++) {
        for (int j = 1; j <= data_per_instance_size; j++) {
            std::cout << "K(" + std::to_string(i) + ") num:" + std::to_string(j) << std::endl;
            std::unique_ptr<ts_instance> instance = helper::create_synthetic_instance(i);

            // solve
            auto start = std::chrono::high_resolution_clock::now();
            const auto &solve_paths = instance->solve();
            auto time = std::chrono::high_resolution_clock::now() - start;
            data_to_csv.push_back(std::to_string(i) + ", branch_bound, " + std::to_string(time.count()));
            instance->reset_solution();

            // brute force solve
            start = std::chrono::high_resolution_clock::now();
            const auto &brute_force_paths = instance->brute_force_solve();
            time = std::chrono::high_resolution_clock::now() - start;
            data_to_csv.push_back(std::to_string(i) + ", brute_force, " + std::to_string(time.count()));

            // test the correctness
            const std::set<std::vector<node> > solveResult = helper::convert_to_node_set(solve_paths);
            const std::set<std::vector<node> > bruteForceResult = helper::convert_to_node_set(
                brute_force_paths);
        }
    }
    // write the statistics into csv
    write_to_csv(data_to_csv, "solve_vs_brute_force.csv");
}

void compare_bb_and_bb_parallel() {
    int max_instance_size = 13;
    int data_per_instance_size = 20;

    for (int i = 3; i <= max_instance_size; i++) {
        for (int j = 1; j <= data_per_instance_size; j++) {
            std::cout << "K(" + std::to_string(i) + ") num:" + std::to_string(j) << std::endl;
            std::unique_ptr<ts_instance> instance = helper::create_synthetic_instance(i);

            // solve
            auto start = std::chrono::high_resolution_clock::now();
            const auto &solve_paths = instance->solve();
            auto time = std::chrono::high_resolution_clock::now() - start;
            data_to_csv.push_back(std::to_string(i) + ", bb, " + std::to_string(time.count()));
            instance->reset_solution();

            // brute force solve
            start = std::chrono::high_resolution_clock::now();
            const auto &brute_force_paths = instance->solve(10);
            time = std::chrono::high_resolution_clock::now() - start;
            data_to_csv.push_back(std::to_string(i) + ", bb_parallel, " + std::to_string(time.count()));

            // test the correctness
            const std::set<std::vector<node> > solveResult = helper::convert_to_node_set(solve_paths);
            const std::set<std::vector<node> > solve_parallel_result = helper::convert_to_node_set(
                brute_force_paths);
        }
    }
    // write the statistics into csv
    write_to_csv(data_to_csv, "solve_vs_solve_parallel.csv");
}

void compare_parallel_with_different_num_of_threads() {
    int instance_size = 8;
    size_t max_number_of_threads = std::thread::hardware_concurrency();
    int data_per_algo = 20;

    for (size_t j = 1; j <= data_per_algo; j++) {
        std::cout << "K(" + std::to_string(instance_size) + ") num:" + std::to_string(j) << std::endl;
        std::unique_ptr<ts_instance> instance = helper::create_synthetic_instance(instance_size);
        for (size_t i = 2; i <= max_number_of_threads; i++) {
            // solve
            auto start = std::chrono::high_resolution_clock::now();
            const auto &solve_paths = instance->solve(i);
            auto time = std::chrono::high_resolution_clock::now() - start;
            data_to_csv.push_back(std::to_string(i) + " ," + std::to_string(time.count()));
        }
        instance->reset_solution();
    }
    write_to_csv(data_to_csv, "comparing_different_num_of_threads.csv");
}

int main() {
    set_stats_up();
    compare_brute_force_solve();
    compare_bb_and_bb_parallel();
    compare_parallel_with_different_num_of_threads();
}
