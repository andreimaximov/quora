#include <string>

#ifndef SRC_ITEM_H_
#define SRC_ITEM_H_

enum ItemType {
    USER, TOPIC, QUESTION, BOARD
};

typedef struct {
    ItemType type;
    std::string id;
    double score;
    std::string data;
} Item;

#endif  // SRC_ITEM_H_
