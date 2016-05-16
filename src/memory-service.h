#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <memory>
#include "item.h"
#include "query.h"
#include "trie.h"
#include "trie-multi-map.h"

#ifndef SRC_MEMORY_SERVICE_H_
#define SRC_MEMORY_SERVICE_H_

class MemoryService {
 private:
  class Entry {
   public:
    typedef std::shared_ptr<Entry> shared_ptr;

    Item item;

    uint32_t time;

    trie<std::string> prefixes;

    Entry(const Item& item, uint32_t time);
  };

  class Result {
   public:
    std::string id;

    float score;

    uint32_t time;

    bool operator<(const Result& other) const;
  };

  class Collector {
   private:
    const Query& query;

    const MemoryService& memoryService;

    std::priority_queue<Result> heap;

    std::unordered_set<std::string> cache;

    void init();

    bool matches(const Entry& entry);

    void process(const Entry& entry, float boost);
   public:
    Collector(const Query& query, const MemoryService& memoryService);

    void operator()(const Entry::shared_ptr& entry);

    std::vector<std::string> results();
  };

  trie_multi_map<std::string, Entry::shared_ptr> prefixes;

  std::unordered_map<std::string, Entry::shared_ptr> items;

  uint32_t time;

 public:
  MemoryService();

  void add(const Item& item);

  void del(const std::string& id);

  std::vector<std::string> query(const Query& query);
};

#endif  // SRC_MEMORY_SERVICE_H_
