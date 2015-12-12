#include <vector>
#include <iostream>
#include "controller.h"
#include "query.h"
#include "split.h"
#include "item.h"

const std::string Controller::ADD_CMD = "ADD";

const std::string Controller::DEL_CMD = "DEL";

const std::string Controller::QUERY_CMD = "QUERY";

const std::string Controller::WQUERY_CMD = "WQUERY";

Controller::Controller(
    std::shared_ptr<QueryParser> queryParser,
    std::shared_ptr<MemoryService> memoryService,
    std::ostream &os) : out(os) {
    this->queryParser = queryParser;
    this->memoryService = memoryService;
}

void Controller::call(const std::string &command) {
    size_t i = command.find(' ');
    if (i == std::string::npos) {
        throw std::invalid_argument("Could not parse command!");
    }

    std::string action = command.substr(0, i);

    if (action.compare(Controller::ADD_CMD) == 0) {
        this->add(command);
    } else if (action.compare(Controller::DEL_CMD) == 0) {
        this->del(command);
    } else if (action.compare(Controller::QUERY_CMD) == 0) {
        this->query(command);
    } else if (action.compare(Controller::WQUERY_CMD) == 0) {
        this->query(command);
    } else {
        throw std::invalid_argument("Invalid command!");
    }
}

void Controller::add(const std::string &command) {
    std::vector<std::string> tokens = split(command, ' ', 5);
    ItemType type = itemtype(tokens[1]);
    double score = std::stod(tokens[3]);

    Item item {
        type,
        tokens[2],
        score,
        tokens[4]
    };

    this->memoryService->add(item);
}

void Controller::del(const std::string &command) {
    std::vector<std::string> tokens = split(command, ' ');
    this->memoryService->del(tokens[1]);
}

void Controller::query(const std::string &command) {
    Query q = this->queryParser->parse(command);
    std::vector<std::string> results = this->memoryService->query(q);
    for (auto id : results) {
        this->out << id << std::endl;
    }
}
