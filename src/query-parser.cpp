#include <sstream>
#include <algorithm>
#include "query-parser.h"
#include "item.h"
#include "trie.h"

const std::string QueryParser::TYPE_QUERY = "QUERY";

const std::string QueryParser::TYPE_WQUERY = "WQUERY";

void QueryParser::boost(std::istream &istream, Query &query) const {
  std::string token;
  getline(istream, token, ' ');
  uint16_t boosts = std::stoul(token);

  std::string classifier;
  for (uint16_t i = 0; i < boosts; i++) {
    getline(istream, classifier, ':');
    getline(istream, token, ' ');
    double factor = std::stod(token);

    Item::Type type = Item::stotype(classifier);

    if (type == Item::Type::INVALID) {
      query.ids.push_back(std::make_pair(classifier, factor));
    } else {
      query.types[type] = factor;
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
void QueryParser::buildTokens(std::istream &istream, Query &query) const {
  std::vector<std::string> tokens;
  std::string token;
  while (istream >> token) {
    std::transform(token.begin(), token.end(), token.begin(), ::tolower);
    tokens.push_back(token);
  }

  std::sort(tokens.begin(), tokens.end());

  trie<std::string> prefixes;
  for (const std::string &token : tokens) {
    if (prefixes.insert(token)) {
      query.tokens.push_back(token);
    }
  }
}

QueryParser::Type QueryParser::type(const std::string &type) const {
  if (type == QueryParser::TYPE_QUERY) {
    return QueryParser::Type::QUERY;
  } else if (type == QueryParser::TYPE_WQUERY) {
    return QueryParser::Type::WQUERY;
  }
  throw std::invalid_argument("Invalid query type!");
}

Query QueryParser::parse(const std::string &command) const {
  std::stringstream stream(command);

  // Extract the query type.
  std::string token;
  getline(stream, token, ' ');
  QueryParser::Type type = this->type(token);

  // Extract the number of results for this query.
  getline(stream, token, ' ');
  Query query(std::stoi(token));

  // Apply boosts if needed.
  if (type == QueryParser::Type::WQUERY) {
    this->boost(stream, query);
  }

  // Parse the query body.
  this->buildTokens(stream, query);

  return query;
}
