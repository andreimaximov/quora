#include <iostream>
#include <string>
#include "controller.h"

int main() {
    Controller* controller = new Controller;

    int queries;
    std::cin >> queries;
    std::cin.ignore('\n');

    std::string line;
    while (queries > 0) {
        std::getline(std::cin, line);
        controller->call(&line);
        queries--;
    }
    return 0;
}
