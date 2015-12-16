#include <string>
#include <sstream>
#include "query-parser.h"
#include "item.h"
#include "trie.h"

const std::string QueryParser::TYPE_QUERY = "QUERY";

const std::string QueryParser::TYPE_WQUERY = "WQUERY";

void QueryParser::boost(std::istream &istream, Query &query) {
    std::string token;
    getline(istream, token, ' ');
    unsigned int boosts = std::stoul(token);

    std::string classifier;
    for (unsigned int i = 0; i < boosts; i++) {
        getline(istream, classifier, ':');
        getline(istream, token, ' ');
        double factor = std::stod(token);

        Item::Type type = Item::stotype(classifier);

        if (type == Item::Type::INVALID) {
            query.idBoosts[classifier] = factor;
        } else {
            query.typeBoosts[type] = factor;
        }
    }
}

/**
 * Optimizes the query body by ignoring tokens that are prefixes of other
 * tokens.
 *
 * @param istream
 * @param query
 */
void QueryParser::buildTokens(std::istream &istream, Query &query) {
    Trie t;
    std::string token;
    while (getline(istream, token, ' ')) {
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        t.insert(token);
    }
    query.tokens = t.tails();
}

QueryParser::Type QueryParser::type(const std::string &type) {
    if (type == QueryParser::TYPE_QUERY) {
        return QueryParser::Type::QUERY;
    } else if (type == QueryParser::TYPE_WQUERY) {
        return QueryParser::Type::WQUERY;
    }
    throw std::invalid_argument("Invalid query type!");
}

Query QueryParser::parse(const std::string &command) {
    std::stringstream qstream(command);

    // Extract the query type.
    std::string token;
    getline(qstream, token, ' ');
    QueryParser::Type type = this->type(token);

    // Extract the number of results for this query.
    getline(qstream, token, ' ');
    Query query(std::stoi(token));

    // Apply boosts if needed.
    if (type == QueryParser::Type::WQUERY) {
        this->boost(qstream, query);
    }

    // Parse the query body.
    this->buildTokens(qstream, query);

    return query;
}
