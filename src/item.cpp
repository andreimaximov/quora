#include "item.h"

ItemType itemtype(const std::string &str) {
    if (str.compare(USER_TYPE)) {
        return ItemType::USER;
    } else if (str.compare(TOPIC_TYPE)) {
        return ItemType::TOPIC;
    } else if (str.compare(QUESTION_TYPE)) {
        return ItemType::QUESTION;
    } else if (str.compare(BOARD_TYPE)) {
        return ItemType::BOARD;
    }

    throw new std::invalid_argument("Invalid ItemType!");
}
