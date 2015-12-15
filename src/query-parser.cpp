#include <vector>
#include <sstream>
#include "query-parser.h"
#include "split.h"
#include "item.h"
#include "trie.h"

Query QueryParser::parseWQuery(std::istream &stream) {
    std::string token;

    getline(stream, token, ' ');
    Query q(std::stoi(token));

    getline(stream, token, ' ');
    int boosts = std::stoi(token);

    std::string classifier;
    for (size_t i = 2; i < 2 + boosts; i++) {
        getline(stream, classifier, ':');
        getline(stream, token, ' ');
        double factor = std::stod(token);

        ItemType type = itemtype(classifier);

        if (type == ItemType::INVALID) {
            q.idBoosts[classifier] = factor;
        } else {
            q.typeBoosts[type] = factor;
        }
    }

    Trie t;
    while (getline(stream, token, ' ')) {
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        t.insert(token);
    }
    q.tokens = t.tails();

    return q;
}

Query QueryParser::parseQuery(std::istream &stream) {
    std::string token;

    getline(stream, token, ' ');
    Query q(std::stoi(token));

    Trie t;
    while (getline(stream, token, ' ')) {
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        t.insert(token);
    }
    q.tokens = t.tails();

    return q;
}

Query QueryParser::parse(const std::string &query) {
    std::stringstream stream(query);

    std::string type;
    getline(stream, type, ' ');

    if (type.compare("QUERY") == 0) {
        return this->parseQuery(stream);
    } else if (type.compare("WQUERY") == 0) {
        return this->parseWQuery(stream);
    } else {
        throw std::invalid_argument("Invalid query!");
    }
}
