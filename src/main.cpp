#include <iostream>
#include <string>
#include "controller.h"

int main() {
    QueryParser* queryParser = new QueryParser();
    Controller* controller = new Controller(queryParser);

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
