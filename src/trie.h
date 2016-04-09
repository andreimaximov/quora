#include <memory>
#include "trie-map.h"

#ifndef SRC_TRIE_H_
#define SRC_TRIE_H_

template <class Value>
class trie {
 private:
  trie_map<Value, bool> inner;

 public:
  typedef Value value_type;

  trie() {
  }

  trie(const trie& other) = delete;

  trie& operator=(const trie &other) = delete;

  bool insert(const value_type &value) {
    if (this->contains(value)) {
      return false;
    }
    this->inner.insert(std::make_pair(value, true));
    return true;
  }

  void erase(const value_type &value) {
    this->inner.erase(value);
  }

  bool contains(const value_type &value) const {
    return this->inner.contains(value);
  }
};

#endif  // SRC_TRIE_H_
