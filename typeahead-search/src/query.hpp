#include <string>
#include <unordered_map>
#include "item.hpp"

#ifndef SRC_QUERY_HPP_
#define SRC_QUERY_HPP_

struct Query {
  enum Type {
    STANDARD, BOOSTED
  };

  // The maximum number of items to return.
  size_t results;

  Type type;

  // The prefix tokens each item in the result set should contain.
  std::vector<std::string> tokens;

  // The default boost factors for each Item::Type value.
  double typeBoosts[4] = {1, 1, 1, 1};

  // Optional ID specific item boosts.
  std::unordered_map<std::string, double> idBoosts;

  explicit Query(size_t results, Type type);

  double scoreItem(const Item& item) const;
};

#endif  // SRC_QUERY_HPP_
