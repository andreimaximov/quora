#include <vector>
#include <sstream>
#include "query-parser.h"

std::vector<std::string>* QueryParser::split(std::string src, char delimeter) {
    std::vector<std::string>* tokens = new std::vector<std::string>();
    std::stringstream stream(src);
    std::string token;
    while (getline(stream, token, delimeter)) {
        tokens->push_back(token);
    }
    return tokens;
}

Query* QueryParser::parseWQuery(std::string* args) {
    return 0;
}

Query* QueryParser::parseQuery(std::string* args) {
    Query* q = new Query;
    q->typeBoosts = NULL;
    q->idBoosts = NULL;
    q->tokens = this->split(*args, ' ');

    q->results = std::stoi((*q->tokens)[0]);
    q->tokens->erase(q->tokens->begin());
    return q;
}

Query* QueryParser::parse(std::string* query) {
    size_t space = query->find(' ');
    std::string type = query->substr(0, space);
    std::string args = query->substr(space + 1, std::string::npos);
    if (type.compare("QUERY") == 0) {
        return this->parseQuery(&args);
    } else if (type.compare("WQUERY") == 0) {
        return this->parseWQuery(&args);
    } else {
        throw std::invalid_argument("Invalid query!");
    }
}
