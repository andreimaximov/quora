#include <string>
#include <vector>

#ifndef SRC_QUERY_H_
#define SRC_QUERY_H_

struct IDBoost {
  std::string id;

  double boost;
};

struct Query {
  enum Type {
    STANDARD, BOOSTED
  };

  size_t results;

  Type type;

  std::vector<std::string> tokens;

  // The default boost factors for each item type
  double typeBoosts[4] = {1, 1, 1, 1};

  // Optional ID specific item boosts
  std::vector<IDBoost> idBoosts;

  explicit Query(size_t results, Type type) : results(results), type(type) {
  }
};

#endif  // SRC_QUERY_H_
