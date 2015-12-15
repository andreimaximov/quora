#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "item.h"
#include "query.h"
#include "trie-set.h"
#include "trie.h"

#ifndef SRC_MEMORY_SERVICE_H_
#define SRC_MEMORY_SERVICE_H_

struct ItemEntry {
    Item item;

    Trie trie;
};

class MemoryService {
 private:
    TrieSet<std::string> trieSet;

    std::unordered_map<std::string, ItemEntry> items;

    std::ostream &out;

    bool match(const ItemEntry &itemEntry, const Query &query);

 public:
    explicit MemoryService(std::ostream &os); // NOLINT

    void add(Item item);

    void del(const std::string &id);

    std::vector<std::string> query(Query query);

    void status();
};

#endif  // SRC_MEMORY_SERVICE_H_
