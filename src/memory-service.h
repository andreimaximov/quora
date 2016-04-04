#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
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
    Item item;

    uint32_t time;

    trie<std::string> prefixes;

    Entry(const Item &item, uint32_t time);
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

    void init();

    bool matches(const Entry *entry);

    void process(const std::string &id, float boost);
   public:
    Searcher(const Query &query, const MemoryService &memoryService);

    void operator()(const std::string &id);

    std::vector<std::string> results();
  };

  trie_map<std::string, std::string> prefixes;

  std::unordered_map<std::string, std::unique_ptr<Entry>> items;

  uint32_t time;

 public:
  MemoryService();

  void add(const Item &item);

  void del(const std::string &id);

  std::vector<std::string> query(Query query);
};

#endif  // SRC_MEMORY_SERVICE_H_
