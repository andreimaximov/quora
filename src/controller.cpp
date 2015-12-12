#include "controller.h"

const std::string Controller::ADD_CMD = "ADD";

const std::string Controller::DEL_CMD = "DEL";

const std::string Controller::QUERY_CMD = "QUERY";

const std::string Controller::WQUERY_CMD = "WQUERY";

Controller::Controller(QueryParser parser) :
    queryParser(std::move(parser)) {
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
}

void Controller::del(const std::string &command) {
}

std::vector<std::string> Controller::query(const std::string &command) {
    return std::vector<std::string>();
}
