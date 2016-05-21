#include <unordered_set>
#include <algorithm>

#ifndef SRC_INTERSECTION_HPP_
#define SRC_INTERSECTION_HPP_

//
// Returns the intersection of the two sets. The function iterates over the
// smaller set and inserts each element which is present in the other set into
// the intersection set.
//
template<typename ValueType>
std::unordered_set<ValueType> intersection(
    const std::unordered_set<ValueType>& lhs,
    const std::unordered_set<ValueType>& rhs) {
  if (lhs.size() > rhs.size()) {
    return intersection(rhs, lhs);
  }
  std::unordered_set<ValueType> intersect;
  for (auto it = lhs.begin(); it != lhs.end(); ++it) {
    auto find = rhs.find(*it);
    if (find != rhs.end()) {
      intersect.insert(*it);
    }
  }
  return intersect;
}

#endif  // SRC_INTERSECTION_HPP_
