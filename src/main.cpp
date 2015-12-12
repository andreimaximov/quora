#include <iostream>
#include <string>
#include <map>
#include "controller.h"
#include "item.h"

int main() {
    std::map<std::string, ItemType> typeMap;
    typeMap["USER"] = ItemType::USER;
    typeMap["TOPIC"] = ItemType::TOPIC;
    typeMap["QUESTION"] = ItemType::QUESTION;
    typeMap["BOARD"] = ItemType::BOARD;

    QueryParser* queryParser = new QueryParser(typeMap);
    Controller* controller = new Controller(queryParser);

    std::string line;
    std::getline(std::cin, line);
    int queries = std::stoi(line);

    while (queries > 0) {
        std::getline(std::cin, line);
        controller->call(&line);
        queries--;
    }
    return 0;
}
