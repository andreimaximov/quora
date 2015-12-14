#include <vector>
#include <algorithm>
#include <ctype.h>
#include "query-parser.h"
#include "split.h"
#include "item.h"

Query QueryParser::parseWQuery(const std::string &args) {
    std::vector<std::string> tokens = split(args, ' ');

    Query q(std::stoi(tokens[0]));

    int boosts = std::stoi(tokens[1]);

    for (size_t i = 2; i < 2 + boosts; i++) {
        std::vector<std::string> boostTokens = split(tokens[i], ':');
        double factor = std::stod(boostTokens[1]);

        ItemType type = itemtype(boostTokens[0]);

        if (type == ItemType::INVALID) {
            q.idBoosts[boostTokens[0]] = factor;
        } else {
            q.typeBoosts[type] = factor;
        }
    }

    q.tokens = std::move(tokens);
    q.tokens.erase(q.tokens.begin(), q.tokens.begin() + 2 + boosts);

    for (std::string &str : q.tokens) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    return q;
}

Query QueryParser::parseQuery(const std::string &args) {
    std::vector<std::string> tokens = split(args, ' ');

    Query q(std::stoi(tokens[0]));
    q.tokens = std::move(tokens);
    q.tokens.erase(q.tokens.begin());

    for (std::string &str : q.tokens) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

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
