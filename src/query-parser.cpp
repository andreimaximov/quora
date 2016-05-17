#include <algorithm>
#include "query-parser.hpp"
#include "item.hpp"

const std::string QueryParser::TYPE_QUERY = "QUERY";

const std::string QueryParser::TYPE_WQUERY = "WQUERY";

void QueryParser::applyBoosts(std::istream& in, Query& query) const {
  uint16_t boosts;
  in >> boosts;

  std::string boost;
  for (uint16_t i = 0; i < boosts; i++) {
    in >> boost;
    // Parse the classifier and boost factor
    std::string::size_type position = boost.find(':');
    if (position == std::string::npos) {
        continue;
    }
    std::string classifier = boost.substr(0, position);
    double factor = std::stod(boost.substr(position + 1));

    Item::Type type = Item::stotype(classifier);

    // If the classifier is not a valid Item::Type then it must be an ID.
    if (type == Item::Type::INVALID) {
      query.idBoosts[classifier] = factor;
    } else {
      query.typeBoosts[type] = factor;
    }
  }
}

void QueryParser::applyTokens(std::istream &in, Query &query) const {
  std::string token;
  while (in >> token) {
    std::transform(token.begin(), token.end(), token.begin(), ::tolower);
    query.tokens.push_back(token);
  }
}

Query QueryParser::parse(Query::Type type, std::istream& in) const {
  // Extract the number of results for this query.
  size_t results;
  in >> results;
  Query query(results, type);

  // Apply boosts if needed.
  if (type == Query::Type::BOOSTED) {
    this->applyBoosts(in, query);
  }

  // Parse the query body.
  this->applyTokens(in, query);

  return query;
}
