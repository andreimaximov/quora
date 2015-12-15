#include <string>

#ifndef SRC_ITEM_H_
#define SRC_ITEM_H_

enum ItemType {
    USER, TOPIC, QUESTION, BOARD, INVALID
};

struct Item {
    static int64_t count;

    ItemType type;
    std::string id;
    double score;
    std::string data;
    int64_t time;
};

const std::string USER_TYPE = "user";

const std::string TOPIC_TYPE = "topic";

const std::string QUESTION_TYPE = "question";

const std::string BOARD_TYPE = "board";

ItemType itemtype(const std::string &str);

#endif  // SRC_ITEM_H_
