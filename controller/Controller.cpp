//
// Created by Jakub Janak on 9/15/24.
//

#include "Controller.h"
#include "../files/FileManager.h"

#include <iostream>
#include <random>
#include <filesystem>
#include <fstream>
#include <string>

void Controller::printHeader() {
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

void Controller::run(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        std::string parameter = argv[i];
        if (parameter == "-li") {
            // loadInstance
            this->loadInstance();
        } else if (parameter == "-alis") {
            // autoLoadInstances
            this->autoLoadInstances();
        } else if (parameter == "-csi") {
            // createSyntheticInstance
            this->createSyntheticInstance();
        } else if (parameter == "-solve") {
            this->solve("");
        } else if (parameter == "-solve-p") {
            this->solve("-p");
        } else if (parameter == "-hc") {
            // heuristicCombination
            this->heuristicCombo();
        } else {
            std::cout << "Unknown Command: " << parameter << std::endl;
        }
    }

    std::cout << "Program Ended!" << std::endl;
}

void Controller::showHelp() {
    std::cout << std::endl;
    std::cout << "####################Travelling Salesman Help:####################" << std::endl;
    std::cout << "li: load instances from a path" << std::endl;
    std::cout << "alis: auto load instances from a path" << std::endl;
    std::cout << "csi: create synthetic instance" << std::endl;
    std::cout << "solve: solve the buffered instances" << std::endl;
    std::cout << "solve -p: solve with parallelization" << std::endl;
    std::cout << "hc: approximate using nearest-neighbour & 2-Opt" << std::endl;
    std::cout << "exit: exit the program" << std::endl << std::endl;
    std::cout << "If unknown command xxx is given the program will respond with:" << std::endl;
    std::cout << "Unknown Command: xxx" << std::endl;
    std::cout << "#################################################################" << std::endl << std::endl;
}

void Controller::loadInstance() {
    std::string filePath;

    std::cout << "file path: ";
    std::getline(std::cin, filePath);

    std::unique_ptr<TSInstance> tsInstance = FileManager::readDotFile(filePath);
    if (tsInstance == nullptr) {
        return;
    }
    this->unsolvedInstances.push_back(std::move(tsInstance));
}

void Controller::autoLoadInstances() {
    std::cout << "Loading all instances from " << FileManager::INSTANCES_PATH << " automatically" << std::endl;
    for (const auto &entry: FileManager::getDotInstances(FileManager::INSTANCES_PATH)) {
        std::unique_ptr<TSInstance> tsInstance = FileManager::readDotFile(entry.path().string());
        this->unsolvedInstances.push_back(std::move(tsInstance));
    }
}

void Controller::createSyntheticInstance() {
    std::string userInput;

    std::cout << "number of nodes: ";
    std::getline(std::cin, userInput);
    const int numOfNodes = std::stoi(userInput);
    this->unsolvedInstances.push_back(TSInstance::createSyntheticInstance(numOfNodes));
}

void Controller::solve(const std::string &args) {
    if (this->unsolvedInstances.empty()) {
        std::cout << "Nothing to solve!" << std::endl;
        return;
    }
    while (!this->unsolvedInstances.empty()) {
        std::cout << "Solving..." << std::endl;
        auto &instance = this->unsolvedInstances.front();
        instance->solve(args);
        instance->printStatistics();
        if (!instance->isSolved()) {
            this->unsolvedInstances.pop_front();
            continue;
        }
        std::string userInput;
        std::cout << "Save the result graph[y for yes]: ";
        std::getline(std::cin, userInput);
        if (userInput == "y") {
            std::cout << "Name of the file: ";
            std::getline(std::cin, userInput);
            instance->saveAs(userInput);
        }
        this->unsolvedInstances.pop_front();
    }
}

void Controller::heuristicCombo() {
    if (this->unsolvedInstances.empty()) {
        std::cout << "Nothing to approximate!" << std::endl;
        return;
    }
    while (!this->unsolvedInstances.empty()) {
        auto &instance = this->unsolvedInstances.front();
        const double result = instance->heuristicCombo();
        std::cout << std::endl << instance->toString() << std::endl;
        std::cout << "Heuristic Approximation: " << result << std::endl;
        this->unsolvedInstances.pop_front();
    }
}
