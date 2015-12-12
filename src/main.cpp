#include <iostream>
#include <string>
#include <map>
#include "controller.h"
#include "item.h"

int main() {
    QueryParser queryParser;
    Controller controller(queryParser);

    std::string line;
    std::getline(std::cin, line);
    int queries = std::stoi(line);

    while (queries > 0) {
        std::getline(std::cin, line);
        controller.call(line);
        queries--;
    }
    return 0;
}
