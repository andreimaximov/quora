#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "item.h"
#include "query.h"
#include "trie-set.h"

#ifndef SRC_MEMORY_SERVICE_H_
#define SRC_MEMORY_SERVICE_H_

struct ItemEntry {
    Item item;
    std::vector<std::string> tokens;
};

class MemoryService {
 private:
    TrieSet<std::string> trie;

    std::unordered_map<std::string, ItemEntry> items;

    std::ostream &out;

 public:
    explicit MemoryService(std::ostream &os); // NOLINT

    virtual void add(Item item);

    virtual void del(const std::string &id);

    virtual std::vector<std::string> query(Query query);

    virtual void status();
};

#endif  // SRC_MEMORY_SERVICE_H_
