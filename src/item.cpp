#include "item.h"

uint64_t Item::count = 0;

const std::string Item::TYPE_USER = "user";

const std::string Item::TYPE_TOPIC = "topic";

const std::string Item::TYPE_QUESTION = "question";

const std::string Item::TYPE_BOARD = "board";

Item::Type Item::stotype(const std::string &str) {
    if (str == Item::TYPE_USER) {
        return Item::Type::USER;
    } else if (str == Item::TYPE_TOPIC) {
        return Item::Type::TOPIC;
    } else if (str == Item::TYPE_QUESTION) {
        return Item::Type::QUESTION;
    } else if (str == Item::TYPE_BOARD) {
        return Item::Type::BOARD;
    }
    return Item::Type::INVALID;
}
