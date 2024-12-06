#include "file_manager.hpp"
#include "../graph/ts_instance.hpp"
#include "../graph/node.hpp"
#include "../graph/edge.hpp"

#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <fstream>
#include <iostream>
#include <map>

const std::string file_manager::INSTANCES_PATH = "../files/instances";

const std::string file_manager::RESULTS_PATH = "../files/results";

// TODO: refactor the read dot file
std::unique_ptr<ts_instance> file_manager::read_dot_file(const std::string &file_name) {
    // graphviz context
    GVC_t *gvc = gvContext();

    // Open the .dot file
    FILE *file = fopen(file_name.c_str(), "r");
    if (!file) {
        std::cout << "Error opening file: " << file_name << " in: " << INSTANCES_PATH << std::endl;
        return nullptr;
    }

    // Parse the .dot file into a graph (digraph)
    Agraph_t *graph = agread(file, nullptr);
    fclose(file);

    if (!graph) {
        std::cout << "Error reading DOT file: " << file_name << std::endl;
        return nullptr;
    }

    // Check if the graph is a digraph
    if (!agisdirected(graph)) {
        std::cout << "The graph in the file is not a directed graph (digraph)." << std::endl;
        agclose(graph);
        gvFreeContext(gvc);
        return nullptr;
    }

    // graph variables
    std::map<std::string, std::unique_ptr<node> > nodesMap;
    std::vector<std::shared_ptr<node> > nodes;
    std::vector<std::shared_ptr<edge> > edges;

    // Iterate over the nodes
    for (Agnode_t *n = agfstnode(graph); n; n = agnxtnode(graph, n)) {
        std::string nodeName = agnameof(n);
        nodesMap.insert(std::make_pair(nodeName, std::make_unique<node>(nodeName)));
    }

    // Iterate over the edges (directed)
    for (Agnode_t *node = agfstnode(graph); node; node = agnxtnode(graph, node)) {
        for (Agedge_t *e = agfstout(graph, node); e; e = agnxtout(graph, e)) {
            Agnode_t *tail = agtail(e); // Source node
            Agnode_t *head = aghead(e); // Destination node

            const std::string weightStr = agget(e, const_cast<char*>("weight"));
            double weight = std::stod(weightStr);

            auto edgePtr = std::make_unique<edge>(
                nodesMap[agnameof(tail)].get(),
                nodesMap[agnameof(head)].get(),
                weight
            );
            nodesMap[agnameof(tail)]->add_edge(edgePtr.get());
            edges.push_back(std::move(edgePtr));
        }
    }

    // Free the graph and close the context
    agclose(graph);
    gvFreeContext(gvc);

    // transforming nodesMap to nodes vector
    nodes.reserve(nodesMap.size());
    for (auto &[fst, snd]: nodesMap) {
        nodes.push_back(std::move(snd));
    }

    return std::make_unique<ts_instance>(std::move(nodes), std::move(edges));
}

std::vector<std::filesystem::directory_entry> file_manager::get_dot_instances(const std::string& directory_path) {
    std::vector<std::filesystem::directory_entry> entries;
    for (const auto &entry: std::filesystem::directory_iterator(directory_path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".dot") {
            std::cout << "found: " << entry.path().filename() << std::endl;
            entries.push_back(entry);
        }
    }
    return entries;
}

void file_manager::folder_exists_check() {
    if (!std::filesystem::exists(RESULTS_PATH)) {
        if (std::filesystem::create_directory(RESULTS_PATH)) {
            std::cout << "Created results directory: " << RESULTS_PATH << std::endl;
        } else {
            std::cout << "Error creating results directory: " << RESULTS_PATH << std::endl;
        }
    }
}

void file_manager::file_naming_conflicts_check(const std::string &file_name, std::string &output_file) {
    int num = 1;
    do {
        std::string number_string = (num == 1) ? "" : "_" + std::to_string(num);
        output_file = RESULTS_PATH + "/" + file_name + number_string + ".dot";
        num++;
    } while (std::filesystem::exists(output_file));
}

void file_manager::save_solution(const std::string &file_name, const std::string &file_content) {
    // creating the results folder if not exists
    folder_exists_check();

    // check for output file conflicts
    std::string output_file;
    file_naming_conflicts_check(file_name, output_file);

    // Check if the file is open
    if (std::ofstream outFile(output_file); outFile.is_open()) {
        // Write the string to the file
        outFile << file_content;

        // Close the file
        outFile.close();

        std::cout << "File saved successfully!" << std::endl;
    } else {
        std::cout << "Error opening the file!" << std::endl;
    }
}
