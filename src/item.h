#include <string>

#ifndef SRC_ITEM_H_
#define SRC_ITEM_H_

class Item {
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

  float score;

  std::string body;

  Item(Type type, std::string id, double score, std::string body) :
  type(type),
  id(id),
  score(score),
  body(body) {
  }
};

#endif  // SRC_ITEM_H_
