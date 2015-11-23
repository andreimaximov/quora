#include <string>
#include "controller.h"

const std::string Controller::ADD_CMD = "ADD";

const std::string Controller::DEL_CMD = "DEL";

const std::string Controller::QUERY_CMD = "QUERY";

const std::string Controller::WQUERY_CMD = "WQUERY";

void Controller::call(std::string* command) {
    COMMAND cmd = this->getCommand(command);
    switch (cmd) {
        case COMMAND::ADD: break;
        case COMMAND::DEL: break;
        case COMMAND::QUERY: break;
        case COMMAND::WQUERY: break;
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
