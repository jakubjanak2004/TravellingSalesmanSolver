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
    std::cout << "********************************************" << std::endl;
    std::cout << "*                                          *" << std::endl;
    std::cout << "*       TTTTTTTT   SSSSSSS   SSSSSSS       *" << std::endl;
    std::cout << "*          TT      SS        SS            *" << std::endl;
    std::cout << "*          TT      SSSSSSS   SSSSSSS       *" << std::endl;
    std::cout << "*          TT           SS        SS       *" << std::endl;
    std::cout << "*          TT      SSSSSSS   SSSSSSS       *" << std::endl;
    std::cout << "*                                          *" << std::endl;
    std::cout << "********************************************" << std::endl;
    std::cout << "\033[0m";
}

void Controller::run() {
    std::string userInput;

    printHeader();
    do {
        std::cout << "Command: ";
        std::getline(std::cin, userInput);

        this->response(userInput);
    } while (userInput != "exit");
    std::cout << "Exiting the program" << std::endl;
}

void Controller::response(const std::string &userInput) {
    if (userInput == "--help") {
        showHelp();
    } else if (userInput == "li") {
        // loadInstance
        this->loadInstance();
    } else if (userInput == "alis") {
        // autoLoadInstances
        this->autoLoadInstances();
    } else if (userInput == "csi") {
        // createSyntheticInstance
        this->createSyntheticInstance();
    } else if (userInput == "solve") {
        this->solve("");
    } else if (userInput == "solve -p") {
        this->solve("-p");
    } else if (userInput == "hc") {
        // heuristicCombination
        this->heuristicCombo();
    } else if (userInput == "exit") {
        // do nothing as the do-while loop will end
    } else {
        std::cout << "Unknown Command: " << userInput << std::endl;
    }
}

void Controller::showHelp() {
    std::cout << "showing help" << std::endl;
}

void Controller::loadInstance() {
    std::string filePath;

    std::cout << "file path: ";
    std::getline(std::cin, filePath);

    const std::unique_ptr<TSInstance> tsInstance = FileManager::readDotFile(filePath);
    if (tsInstance == nullptr) {
        return;
    }
    this->unsolvedInstances.push(std::move(*tsInstance));
}

void Controller::autoLoadInstances() {
    std::cout << "Loading all instances from " << FileManager::INSTANCES_PATH << " automatically" << std::endl;
    for (const auto &entry: FileManager::getDotInstances(FileManager::INSTANCES_PATH)) {
        std::unique_ptr<TSInstance> tsInstance = FileManager::readDotFile(entry.path().string());
        this->unsolvedInstances.push(std::move(*tsInstance));
    }
}

void Controller::createSyntheticInstance() {
    std::string userInput;

    std::cout << "number of nodes: ";
    std::getline(std::cin, userInput);
    const int numOfNodes = std::stoi(userInput);
    this->unsolvedInstances.emplace(TSInstance::createSyntheticInstance(numOfNodes));
}

void Controller::solve(const std::string &args) {
    if (this->unsolvedInstances.empty()) {
        std::cout << "Nothing to solve!" << std::endl;
        return;
    }
    while (!this->unsolvedInstances.empty()) {
        auto &instance = this->unsolvedInstances.front();
        instance.solve(args);
        instance.printStatistics();
        if (!instance.isSolved()) {
            this->unsolvedInstances.pop();
            continue;
        }
        std::string userInput;
        std::cout << "Save the result graph[y for yes]: ";
        std::getline(std::cin, userInput);
        if (userInput == "y") {
            std::cout << "Name of the file: ";
            std::getline(std::cin, userInput);
            instance.saveAs(userInput);
        }
        this->unsolvedInstances.pop();
    }
}

void Controller::heuristicCombo() {
    if (this->unsolvedInstances.empty()) {
        std::cout << "Nothing to approximate!" << std::endl;
        return;
    }
    while (!this->unsolvedInstances.empty()) {
        auto &instance = this->unsolvedInstances.front();
        const double result = instance.heuristicCombo();
        std::cout << std::endl << instance.toString() << std::endl;
        std::cout << "Heuristic Approximation: " << result << std::endl;
        this->unsolvedInstances.pop();
    }
}
