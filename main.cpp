#include "Core/Controller.h"

int main() {
    Controller* controller = new Controller();

    controller->run();

    delete controller;

    return 0;
}
