#include "controller/Controller.hpp"

int main(int argc, char *argv[]) {
    auto controller = Controller();
    controller.run(argc, argv);
}
