#include <string>

#ifndef SRC_MEMORY_SERVICE_H_
#define SRC_MEMORY_SERVICE_H_

enum ItemType {
    USER, TOPIC, QUESTION, BOARD
};

typedef struct {
    ItemType type;
    std::string id;
    double score;
    std::string data;
} Item;

class MemoryService {
 public:
    virtual void add(Item* item);

    virtual void del(std::string* id);
};

#endif  // SRC_MEMORY_SERVICE_H_
