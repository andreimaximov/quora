#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "item.h"
#include "query.h"

#ifndef SRC_MEMORY_SERVICE_H_
#define SRC_MEMORY_SERVICE_H_

struct ItemEntry {
    Item item;
    std::vector<std::string> tokens;
};

class MemoryService {
 private:
    std::unordered_map<std::string, std::unordered_set<std::string>> tokens;

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
