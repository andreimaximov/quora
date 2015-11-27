#include <vector>
#include <sstream>
#include "query-parser.h"

QueryParser::QueryParser(std::map<std::string, ItemType>* typeMap) {
    this->typeMap = typeMap;
}

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
    Query* q = new Query;
    q->typeBoosts = new std::vector<TypeBoost>();
    q->idBoosts = new std::vector<IdBoost>();
    q->tokens = this->split(*args, ' ');

    q->results = std::stoi((*q->tokens)[0]);

    int boosts = std::stoi((*q->tokens)[1]);

    for (size_t i = 2; i < 2 + boosts; i++) {
        std::vector<std::string>* boostTokens =
            this->split((*q->tokens)[i], ':');

        std::string boostClassifier = (*boostTokens)[0];
        double boostFactor = std::stod((*boostTokens)[1]);

        std::map<std::string, ItemType>::iterator typeIterator =
            this->typeMap->find(boostClassifier);

        if (typeIterator == this->typeMap->end()) {
            IdBoost boost {boostClassifier, boostFactor};
            q->idBoosts->push_back(boost);
        } else {
            TypeBoost boost {typeIterator->second, boostFactor};
            q->typeBoosts->push_back(boost);
        }
    }

    q->tokens->erase(q->tokens->begin(), q->tokens->begin() + 2 + boosts);

    return q;
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
