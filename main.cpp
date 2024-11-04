#include "controller/Controller.h"

#include <iostream>
#include <random>

int main(int argc, char *argv[]) {
    Controller::printHeader();
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--help") {
            Controller::showHelp();
            return 0;
        }
    }

    Controller controller = Controller();
    controller.run(argc, argv);

    // testing the solver on a generated graph
    // test_BB();
}
