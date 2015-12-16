#include <string>

#ifndef SRC_ITEM_H_
#define SRC_ITEM_H_

class Item {
 private:
    static uint64_t count;

 public:
    enum Type {
        USER, TOPIC, QUESTION, BOARD, INVALID
    };

    static const std::string TYPE_USER;

    static const std::string TYPE_TOPIC;

    static const std::string TYPE_QUESTION;

    static const std::string TYPE_BOARD;

    static Type stotype(const std::string &str);

    Type type;

    std::string id;

    double score;

    std::string body;

    uint64_t time;

    Item(Type type, std::string id, double score, std::string body) :
        type(type),
        id(id),
        score(score),
        body(body) {
        this->time = Item::count++;
    }
};

#endif  // SRC_ITEM_H_
