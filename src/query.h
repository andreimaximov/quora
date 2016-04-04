#include <string>
#include <vector>
#include "item.h"

#ifndef SRC_QUERY_H_
#define SRC_QUERY_H_

struct Query {
  size_t results;

  std::vector<std::string> tokens;

  double types[4] = {1, 1, 1, 1};

  std::vector<std::pair<std::string, double>> ids;

  explicit Query(size_t results) : results(results) {
  }
};

#endif  // SRC_QUERY_H_
