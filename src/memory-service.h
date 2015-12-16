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

        double score;

        uint64_t time;

        Trie trie;
    };

    class Result {
     public:
        std::string id;

        double score;

        uint64_t time;

        bool operator<(const Result &other) const;
    };

    class Traverser {
     private:
        Query *query;

        MemoryService *memoryService;

        std::unordered_set<std::string> encountered;

        std::priority_queue<Result> heap;
     public:
        Traverser(Query *query, MemoryService *memoryService);

        bool matches(const Entry &entry);

        double score(const Entry &entry);

        void operator()(const std::string &candidate);

        std::vector<std::string> results();
    };

    TrieMap<std::string> prefixes;

    std::unordered_map<std::string, Entry> items;

    std::ostream &out;

 public:
    explicit MemoryService(std::ostream &os); // NOLINT

    void add(const Item &item);

    void del(const std::string &id);

    std::vector<std::string> query(Query query);

    void status();
};

#endif  // SRC_MEMORY_SERVICE_H_
