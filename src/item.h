#include <string>
#include <vector>

#ifndef SRC_ITEM_H_
#define SRC_ITEM_H_

struct Item {
  enum Type {
    USER = 0, TOPIC = 1, QUESTION = 2, BOARD = 3, INVALID = 4
  };

  static const std::string TYPE_USER;

  static const std::string TYPE_TOPIC;

  static const std::string TYPE_QUESTION;

  static const std::string TYPE_BOARD;

  std::string id;

  Type type;

  float score;

  std::vector<std::string> tokens;

  static Type stotype(const std::string &str);
};

#endif  // SRC_ITEM_H_
