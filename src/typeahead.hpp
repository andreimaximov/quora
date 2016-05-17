#include <string>
#include <vector>
#include <unordered_map>
#include "item.hpp"
#include "query.hpp"
#include "trie.hpp"

#ifndef SRC_TYPEAHEAD_H_
#define SRC_TYPEAHEAD_H_

class Typeahead {
 private:
  trie<std::string, Item*> prefixes;

  std::unordered_map<std::string, Item> items;

  uint32_t order = 0;

  std::vector<const Item*> getTopItems(const Query& query,
                                       const std::unordered_set<Item*> items);
  //
  // Returns the index of the token with the smallest item set
  //
  size_t getSmallestPrefixSet(const Query& query);

 public:
  void add(const Item& item);

  void del(const std::string& id);

  std::vector<const Item*> query(const Query& query);
};

struct Candidate {
  const Item* item;

  double score;
};

bool operator<(const Candidate& lhs, const Candidate& rhs);

#endif  // SRC_TYPEAHEAD_H_
