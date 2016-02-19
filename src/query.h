#include <string>
#include <vector>
#include <unordered_map>
#include "item.h"

#ifndef SRC_QUERY_H_
#define SRC_QUERY_H_

struct Query {
  size_t results;
  std::vector<std::string> tokens;
  std::unordered_map<Item::Type, double, std::hash<int>> typeBoosts;
  std::unordered_map<std::string, double> idBoosts;

  explicit Query(size_t results) {
    this->results = results;
  }
};

#endif  // SRC_QUERY_H_
