#include <vector>
#include "query-parser.h"
#include "split.h"

QueryParser::QueryParser(std::map<std::string, ItemType> types) :
    typeMap(std::move(types)) {
}

Query QueryParser::parseWQuery(const std::string &args) {
    std::vector<std::string> tokens = split(args, ' ');

    Query q(std::stoi(tokens[0]));

    int boosts = std::stoi(tokens[1]);

    for (size_t i = 2; i < 2 + boosts; i++) {
        std::vector<std::string> boostTokens = split(tokens[i], ':');
        double factor = std::stod(boostTokens[1]);

        std::map<std::string, ItemType>::iterator typeIterator =
            this->typeMap.find(boostTokens[0]);

        if (typeIterator == this->typeMap.end()) {
            IdBoost boost(boostTokens[0], factor);
            q.idBoosts.push_back(boost);
        } else {
            TypeBoost boost(typeIterator->second, factor);
            q.typeBoosts.push_back(boost);
        }
    }

    q.tokens.erase(q.tokens.begin(), q.tokens.begin() + 2 + boosts);

    return q;
}

Query QueryParser::parseQuery(const std::string &args) {
    std::vector<std::string> tokens = split(args, ' ');

    Query q(std::stoi(tokens[0]));
    q.tokens = std::move(tokens);
    q.tokens.erase(q.tokens.begin());

    return q;
}

Query QueryParser::parse(const std::string &query) {
    size_t space = query.find(' ');
    std::string type = query.substr(0, space);
    std::string args = query.substr(space + 1, std::string::npos);

    if (type.compare("QUERY") == 0) {
        return this->parseQuery(args);
    } else if (type.compare("WQUERY") == 0) {
        return this->parseWQuery(args);
    } else {
        throw std::invalid_argument("Invalid query!");
    }
}
