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
#include <memory>

// Static method to read a .dot file with a digraph
std::unique_ptr<TSInstance> FileManager::readDotFile(const std::string &filename) {
    // Initialize the Graphviz context
    GVC_t *gvc = gvContext();
    std::map<std::string, std::unique_ptr<Node> > nodesMap;
    std::vector<std::unique_ptr<Node> > nodes;
    std::vector<std::unique_ptr<Edge> > edges;

    // Open the .dot file
    FILE *file = fopen(filename.c_str(), "r");
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return nullptr;
    }

    // Parse the .dot file into a graph (digraph)
    Agraph_t *graph = agread(file, nullptr);
    fclose(file);

    if (!graph) {
        std::cerr << "Error reading DOT file: " << filename << std::endl;
        return nullptr;
    }

    // Check if the graph is a digraph
    if (!agisdirected(graph)) {
        std::cerr << "The graph in the file is not a directed graph (digraph)." << std::endl;
        agclose(graph);
        gvFreeContext(gvc);
        return nullptr;
    }

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

            const char *weightStr = agget(edge, "weight");
            std::string weightString(weightStr);
            double weight = std::stod(weightString);

            auto edgePtr = std::make_unique<Edge>(
                nodesMap[agnameof(tail)].get(),
                nodesMap[agnameof(head)].get(),
                weight
            );
            nodesMap[agnameof(tail)]->addEdge(edgePtr.get());
            edges.push_back(std::move(edgePtr));
        }
    }

    // Free the graph and close the context
    agclose(graph);
    gvFreeContext(gvc);

    // transforming nodesMap to nodes vector
    for (auto &pair: nodesMap) {
        nodes.push_back(std::move(pair.second));
    }

    return std::make_unique<TSInstance>(std::move(nodes), std::move(edges));
}

std::vector<std::filesystem::directory_entry> FileManager::getDotInstances(std::string directoryPath) {
    std::vector<std::filesystem::directory_entry> entries;
    for (const auto &entry: std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".dot") {
            std::cout << "Found: " << entry.path().filename() << std::endl;
            entries.push_back(entry);
        }
    }
    return entries;
}

void FileManager::saveSolution(const std::string &fileName, const std::string &fileContent) {
    std::ofstream outFile("../files/results/" + fileName + ".dot");

    // Check if the file is open
    if (outFile.is_open()) {
        // Write the string to the file
        outFile << fileContent;

        // Close the file
        outFile.close();

        std::cout << "File saved successfully!" << std::endl;
    } else {
        std::cerr << "Error opening the file!" << std::endl;
    }
}
