#include <memory>
#include <unordered_set>
#include "trie-map.h"

#ifndef SRC_TRIE_MULTI_MAP_H_
#define SRC_TRIE_MULTI_MAP_H_

template <class Key, class Value, class Container = std::unordered_set<Value>>
class trie_multi_map {
 private:
  trie_map<Key, Container> inner;

 public:
  typedef std::pair<Key, Value> value_type;

  trie_multi_map() {
  }

  trie_multi_map(const trie_multi_map& other) = delete;

  trie_multi_map& operator=(const trie_multi_map &other) = delete;

  void insert(const value_type &value) {
    Container &values = this->inner[value.first];
    values.insert(value.second);
  }

  void erase(const value_type &value) {
    if (!this->inner.contains(value.first)) {
      return;
    }
    Container &values = this->inner[value.first];
    values.erase(value.second);
  }

  template <class Consumer>
  void each(Consumer &consumer, const Key &key = Key()) const { // NOLINT
    auto wrapper = [&] (const Container &container) mutable { // NOLINT
      for (const Value &value : container) {
        consumer(value);
      }
    };
    this->inner.each(wrapper, key);
  }
};

#endif  // SRC_TRIE_MULTI_MAP_H_
