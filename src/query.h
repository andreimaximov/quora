#include <string>
#include <vector>
#include "item.h"

#ifndef SRC_QUERY_H_
#define SRC_QUERY_H_

struct TypeBoost {
    ItemType type;
    double boost;

    TypeBoost(ItemType type, double boost) {
        this->type = type;
        this->boost = boost;
    }
};

struct IdBoost {
    std::string id;
    double boost;

    IdBoost(const std::string &id, double boost) :
        id(id) {
        this->boost = boost;
    }
};

struct Query {
    unsigned int results;
    std::vector<std::string> tokens;
    std::vector<TypeBoost> typeBoosts;
    std::vector<IdBoost> idBoosts;

    explicit Query(unsigned int results) {
        this->results = results;
    }
};

#endif  // SRC_QUERY_H_
