#include <string>

#ifndef SRC_ITEM_H_
#define SRC_ITEM_H_

class Item {
 public:
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

  std::string body;

  Item(const std::string &id, const Type &type, const double &score,
    const std::string &body);

  static Type stotype(const std::string &str);
};

#endif  // SRC_ITEM_H_
