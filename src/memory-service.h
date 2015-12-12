#include <string>
#include <vector>
#include "item.h"
#include "query.h"

#ifndef SRC_MEMORY_SERVICE_H_
#define SRC_MEMORY_SERVICE_H_

class MemoryService {
 public:
    virtual void add(Item item);

    virtual void del(const std::string &id);

    virtual std::vector<std::string> query(Query query);
};

#endif  // SRC_MEMORY_SERVICE_H_
