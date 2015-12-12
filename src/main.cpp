#include <iostream>
#include <string>
#include <memory>
#include "query-parser.h"
#include "memory-service.h"
#include "controller.h"

int main() {
    auto queryParser = std::make_shared<QueryParser>();

    auto memoryService = std::make_shared<MemoryService>();

    auto controller = std::make_shared<Controller>(
        queryParser,
        memoryService);

    std::string line;
    std::getline(std::cin, line);
    int queries = std::stoi(line);

    while (queries > 0) {
        std::getline(std::cin, line);
        controller->call(line);
        memoryService->status();
        queries--;
    }
    return 0;
}
