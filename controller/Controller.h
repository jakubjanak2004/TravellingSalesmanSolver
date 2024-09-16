//
// Created by Jakub Janak on 9/15/24.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../graph/TSInstance.h"

#include <iostream>
#include <queue>


class Controller {

std::queue<TSInstance> unsolvedInstances;

public:
    void run();

    void response(const std::string &userInput);

    void showHelp();

    void loadInstance();

void autoLoadInstances();

void createSyntheticInstance();

void solve();
};


#endif //CONTROLLER_H
