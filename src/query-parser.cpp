#include <sstream>
#include <algorithm>
#include "query-parser.h"
#include "item.h"

const std::string QueryParser::TYPE_QUERY = "QUERY";

const std::string QueryParser::TYPE_WQUERY = "WQUERY";

void QueryParser::boost(std::istream &istream, Query &query) const {
  std::string token;
  std::getline(istream, token, ' ');
  uint16_t boosts = std::stoul(token);

  std::string classifier;
  for (uint16_t i = 0; i < boosts; i++) {
    std::getline(istream, classifier, ':');
    std::getline(istream, token, ' ');
    double factor = std::stod(token);

    Item::Type type = Item::stotype(classifier);

    if (type == Item::Type::INVALID) {
      query.ids.push_back(std::make_pair(classifier, factor));
    } else {
      query.types[type] = factor;
    }
  }
}

void QueryParser::applyTokens(std::istream &istream, Query &query) const {
  std::vector<std::string> tokens;
  std::string token;
  while (istream >> token) {
    std::transform(token.begin(), token.end(), token.begin(), ::tolower);
    query.tokens.push_back(token);
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
  std::getline(stream, token, ' ');
  QueryParser::Type type = this->type(token);

  // Extract the number of results for this query.
  std::getline(stream, token, ' ');
  Query query(std::stoi(token));

  // Apply boosts if needed.
  if (type == QueryParser::Type::WQUERY) {
    this->boost(stream, query);
  }

  // Parse the query body.
  this->applyTokens(stream, query);

  return query;
}
