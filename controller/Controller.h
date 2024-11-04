//
// Created by Jakub Janak on 9/15/24.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../graph/TSInstance.h"

#include <queue>


class Controller {
    std::deque<std::unique_ptr<TSInstance>> unsolvedInstances;

public:
    static void printHeader();

    void run(int argc, char *argv[]);

    void loadInstance();

    void autoLoadInstances();

    void createSyntheticInstance();

    void solve(const std::string& args);

    void heuristicCombo();

    static void showHelp();
};


#endif //CONTROLLER_H
