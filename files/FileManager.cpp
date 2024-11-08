//
// Created by Jakub Janak on 9/14/24.
//

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

std::unique_ptr<TSInstance> FileManager::readDotFile(const std::string &filename) {
    // graphviz context
    GVC_t *gvc = gvContext();

    // Open the .dot file
    FILE *file = fopen(filename.c_str(), "r");
    if (!file) {
        std::cout << "Error opening file: " << filename << " in: " << INSTANCES_PATH << std::endl;
        return nullptr;
    }

    // Parse the .dot file into a graph (digraph)
    Agraph_t *graph = agread(file, nullptr);
    fclose(file);

    if (!graph) {
        std::cout << "Error reading DOT file: " << filename << std::endl;
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

std::vector<std::filesystem::directory_entry> FileManager::getDotInstances(const std::string& directoryPath) {
    std::vector<std::filesystem::directory_entry> entries;
    for (const auto &entry: std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".dot") {
            std::cout << "found: " << entry.path().filename() << std::endl;
            entries.push_back(entry);
        }
    }
    return entries;
}

void FileManager::saveSolution(const std::string &fileName, const std::string &fileContent) {
    // Check if the file is open
    if (std::ofstream outFile(RESULTS_PATH + "/" + fileName + ".dot"); outFile.is_open()) {
        // Write the string to the file
        outFile << fileContent;

        // Close the file
        outFile.close();

        std::cout << "File saved successfully!" << std::endl;
    } else {
        std::cout << "Error opening the file!" << std::endl;
    }
}
