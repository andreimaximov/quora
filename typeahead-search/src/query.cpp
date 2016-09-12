#include "query.hpp"

Query::Query(size_t results, Type type) : results(results), type(type) {
}

double Query::scoreItem(const Item& item) const {
  double multiplier = this->typeBoosts[item.type];
  auto it = this->idBoosts.find(item.id);
  if (it != this->idBoosts.end()) {
    multiplier *= it->second;
  }
  return multiplier * item.score;
}
