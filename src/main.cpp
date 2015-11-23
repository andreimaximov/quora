#include <iostream>
#include <string>
#include "controller.h"

int main() {
    Controller* controller = new Controller;

    std::string line;
    std::getline(std::cin, line);
    int queries = std::stoi(line);

    while (queries > 0) {
        std::getline(std::cin, line);
        controller->call(&line);
        queries--;
    }
    return 0;
}
