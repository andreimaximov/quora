#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <ostream>
#include "item.h"
#include "query.h"
#include "trie-map.h"
#include "trie.h"

#ifndef SRC_MEMORY_SERVICE_H_
#define SRC_MEMORY_SERVICE_H_

class MemoryService {
 private:
  class Entry {
   public:
    std::string id;

    Item::Type type;

    float score;

    uint32_t time;

    Trie trie;
  };

  class Result {
   public:
    std::string id;

    float score;

    uint32_t time;

    bool operator<(const Result &other) const;
  };

  class Searcher {
   private:
    const Query &query;

    const MemoryService &memoryService;

    std::priority_queue<Result> heap;

    std::unordered_set<std::string> cache;
   public:
    Searcher(const Query &query, const MemoryService &memoryService);

    void init();

    bool matches(const Entry &entry);

    float boost(const Entry &entry);

    void operator()(const std::string &id);

    void process(const std::string &id, float boost);

    std::vector<std::string> results();
  };

  TrieMap<std::string> prefixes;

  std::unordered_map<std::string, Entry> items;

  std::ostream &out;

  static uint32_t time;

 public:
  explicit MemoryService(std::ostream &os); // NOLINT

  void add(const Item &item);

  void del(const std::string &id);

  std::vector<std::string> query(Query query);

  void status();
};

#endif  // SRC_MEMORY_SERVICE_H_
