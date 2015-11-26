#include <string>
#include <vector>
#include "item.h"

#ifndef SRC_QUERY_H_
#define SRC_QUERY_H_

typedef struct {
    ItemType type;
    double boost;
} TypeBoost;

typedef struct {
    std::string* id;
    double boost;
} IdBoost;

typedef struct {
    int results;
    std::vector<std::string>* tokens;
    std::vector<TypeBoost>* typeBoosts;
    std::vector<IdBoost>* idBoosts;
} Query;

#endif  // SRC_QUERY_H_
