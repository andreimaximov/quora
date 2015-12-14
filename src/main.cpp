#include <iostream>
#include <string>
#include <memory>
#include "query-parser.h"
#include "memory-service.h"
#include "controller.h"

int main() {
    auto queryParser = std::make_shared<QueryParser>();

    auto memoryService = std::make_shared<MemoryService>(std::cout);

    auto controller = std::make_shared<Controller>(
        queryParser,
        memoryService,
        std::cout);

    std::string line;
    std::getline(std::cin, line);
    int queries = std::stoi(line);

    while (queries > 0) {
        std::getline(std::cin, line);
        std::cout << line << std::endl;
        controller->call(line);
        queries--;
    }
    return 0;
}
