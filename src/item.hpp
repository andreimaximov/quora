#include <string>
#include <vector>

#ifndef SRC_ITEM_H_
#define SRC_ITEM_H_

struct Item {
  // Item types
  enum Type {
    USER = 0, TOPIC = 1, QUESTION = 2, BOARD = 3, INVALID = 4
  };

  static const std::string TYPE_USER;

  static const std::string TYPE_TOPIC;

  static const std::string TYPE_QUESTION;

  static const std::string TYPE_BOARD;

  // The unique Item ID
  std::string id;

  Type type;

  float score;

  // The lowercase string tokens of this item
  std::vector<std::string> tokens;

  // The insertion order ID of the item
  uint32_t order = 0;

  // Parses the string into an Item::Type
  static Type stotype(const std::string& str);
};

#endif  // SRC_ITEM_H_
