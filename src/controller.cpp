#include <vector>
#include <iostream>
#include <algorithm>
#include "controller.h"
#include "query.h"
#include "split.h"
#include "item.h"

const std::string Controller::CMD_ADD = "ADD";

const std::string Controller::CMD_DEL = "DEL";

const std::string Controller::CMD_QUERY = "QUERY";

const std::string Controller::CMD_WQUERY = "WQUERY";

Controller::Controller(
  const QueryParser &queryParser,
  MemoryService &memoryService,
  std::ostream &os) :
    queryParser(queryParser),
    memoryService(memoryService),
    out(os) {
  }

  void Controller::call(const std::string &command) {
    size_t space = command.find(' ');
    if (space == std::string::npos) {
      throw std::invalid_argument("Could not parse command!");
    }
    std::string action = command.substr(0, space);

    if (action == Controller::CMD_ADD) {
      this->add(command);
    } else if (action == Controller::CMD_DEL) {
      this->del(command);
    } else if (action == Controller::CMD_QUERY) {
      this->query(command);
    } else if (action == Controller::CMD_WQUERY) {
      this->query(command);
    } else {
      throw std::invalid_argument("Invalid command!");
    }
  }

  void Controller::add(const std::string &command) {
    std::vector<std::string> tokens = split(command, ' ');
    Item::Type type = Item::stotype(tokens[1]);
    std::string id = tokens[2];
    double score = std::stod(tokens[3]);

    tokens.erase(tokens.begin(), tokens.begin() + 4);
    for (std::string &token : tokens) {
      std::transform(token.begin(), token.end(), token.begin(), ::tolower);
    }

    Item item(id, type, score, tokens);
    this->memoryService.add(item);
  }

  void Controller::del(const std::string &command) {
    std::vector<std::string> tokens = split(command, ' ');
    this->memoryService.del(tokens[1]);
  }

  void Controller::query(const std::string &command) {
    Query query = this->queryParser.parse(command);
    std::vector<std::string> results = this->memoryService.query(query);

    std::string space("");
    for (std::string &id : results) {
      this->out << space << id;
      space = " ";
    }
    this->out << std::endl;
  }
