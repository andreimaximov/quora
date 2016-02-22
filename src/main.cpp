#include <iostream>
#include <string>
#include <memory>
#include "query-parser.h"
#include "memory-service.h"
#include "controller.h"

int main() {
  QueryParser queryParser;
  MemoryService memoryService(std::cout);
  Controller controller(queryParser, memoryService, std::cout);

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
