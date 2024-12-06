#include "FileManager.h"
#include "../graph/TSInstance.h"
#include "../graph/Node.h"
#include "../graph/Edge.h"

#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <fstream>
#include <iostream>
#include <map>

const std::string FileManager::INSTANCES_PATH = "../files/instances";

const std::string FileManager::RESULTS_PATH = "../files/results";

std::unique_ptr<TSInstance> FileManager::read_dot_file(const std::string &file_name) {
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
    std::map<std::string, std::unique_ptr<Node> > nodesMap;
    std::vector<std::shared_ptr<Node> > nodes;
    std::vector<std::shared_ptr<Edge> > edges;

    // Iterate over the nodes
    for (Agnode_t *node = agfstnode(graph); node; node = agnxtnode(graph, node)) {
        std::string nodeName = agnameof(node);
        nodesMap.insert(std::make_pair(nodeName, std::make_unique<Node>(nodeName)));
    }

    // Iterate over the edges (directed)
    for (Agnode_t *node = agfstnode(graph); node; node = agnxtnode(graph, node)) {
        for (Agedge_t *edge = agfstout(graph, node); edge; edge = agnxtout(graph, edge)) {
            Agnode_t *tail = agtail(edge); // Source node
            Agnode_t *head = aghead(edge); // Destination node

            const std::string weightStr = agget(edge, const_cast<char*>("weight"));
            double weight = std::stod(weightStr);

            auto edgePtr = std::make_unique<Edge>(
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

    return std::make_unique<TSInstance>(std::move(nodes), std::move(edges));
}

std::vector<std::filesystem::directory_entry> FileManager::get_dot_instances(const std::string& directory_path) {
    std::vector<std::filesystem::directory_entry> entries;
    for (const auto &entry: std::filesystem::directory_iterator(directory_path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".dot") {
            std::cout << "found: " << entry.path().filename() << std::endl;
            entries.push_back(entry);
        }
    }
    return entries;
}

void FileManager::save_solution(const std::string &file_name, const std::string &file_content) {
    // creating the results folder if not exists
    if (!std::filesystem::exists(RESULTS_PATH)) {
        if (std::filesystem::create_directory(RESULTS_PATH)) {
            std::cout << "Created results directory: " << RESULTS_PATH << std::endl;
        } else {
            std::cout << "Error creating results directory: " << RESULTS_PATH << std::endl;
        }
    }

    // check for output file conflicts
    int num = 1;
    std::string output_file;
    do {
        std::string number_string = (num == 1) ? "" : "_" + std::to_string(num);
        output_file = RESULTS_PATH + "/" + file_name + number_string + ".dot";
        num++;
    } while (std::filesystem::exists(output_file));

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
