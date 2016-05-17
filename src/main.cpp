#include <iostream>
#include <string>
#include "query-parser.hpp"
#include "typeahead.hpp"
#include "controller.hpp"

int main() {
  QueryParser queryParser;
  Typeahead typeahead;
  Controller controller(queryParser, typeahead, std::cout);

  std::string line;
  std::getline(std::cin, line);
  int queries = std::stoi(line);

  while (queries > 0) {
    std::getline(std::cin, line);
    controller.execute(line);
    queries--;
  }
  return 0;
}
