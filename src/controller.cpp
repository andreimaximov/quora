#include <string>
#include <vector>
#include "controller.h"

const std::string Controller::ADD_CMD = "ADD";

const std::string Controller::DEL_CMD = "DEL";

const std::string Controller::QUERY_CMD = "QUERY";

const std::string Controller::WQUERY_CMD = "WQUERY";

void Controller::call(std::string* command) {
    COMMAND cmd = this->getCommand(command);
    switch (cmd) {
        case COMMAND::ADD: this->add(command);
            break;
        case COMMAND::DEL: this->del(command);
            break;
        case COMMAND::QUERY: this->query(command);
            break;
        case COMMAND::WQUERY: this->wquery(command);
            break;
    }
}

COMMAND Controller::getCommand(std::string* command) {
    size_t i = command->find_first_of(' ');
    if (i == std::string::npos) {
        throw std::invalid_argument("Could not parse command!");
    }

    std::string cmd = command->substr(0, i + 1);
    if (cmd.compare(Controller::ADD_CMD) != 0) {
        return COMMAND::ADD;
    } else if (cmd.compare(Controller::DEL_CMD) != 0) {
        return COMMAND::DEL;
    } else if (cmd.compare(Controller::QUERY_CMD) != 0) {
        return COMMAND::QUERY;
    } else if (cmd.compare(Controller::WQUERY_CMD) != 0) {
        return COMMAND::WQUERY;
    }

    throw std::invalid_argument("Invalid command!");
}

void Controller::add(std::string* command) {
}

void Controller::del(std::string* command) {
}

std::vector<std::string>* Controller::query(std::string* command) {
    return 0;
}

std::vector<std::string>* Controller::wquery(std::string* command) {
    return 0;
}
