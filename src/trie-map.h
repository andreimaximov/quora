#include <unordered_set>
#include <map>
#include <memory>

#ifndef SRC_TRIE_MAP_H_
#define SRC_TRIE_MAP_H_

template <class K, class V>
class trie_map {
 private:
  class node {
   public:
    typedef std::unique_ptr<node> u_ptr;

    typedef std::map<typename K::value_type, u_ptr> child_map;

    std::unordered_set<V> values;

    child_map children;

    node() {
    }

    node(const node& other) = delete; // NOLINT

    node& operator=(const node &other) = delete;
  };

  node* at(const K &key) {
    node* n = &this->root;
    for (const auto &k : key) {
      auto iter = n->children.find(k);
      if (iter == n->children.end()) {
        return nullptr;
      }
      n = iter->second.get();
    }
    return n;
  }

  template <class F>
  void each(F &f, node* n) { // NOLINT
    for (const V &value : n->values) {
      f(value);
    }
    for (const auto &pair : n->children) {
      this->each(f, pair.second.get());
    }
  }

 public:
  typedef std::pair<K, V> value_type;

  trie_map() {
  }

  trie_map(const trie_map& other) = delete;

  trie_map& operator=(const trie_map &other) = delete;

  void insert(const value_type &value) {
    node* n = &this->root;
    for (const auto &k : value.first) {
      auto iter = n->children.find(k);
      if (iter == n->children.end()) {
        node *child = new node;
        n->children[k] = std::unique_ptr<node>(child);
        n = child;
      } else {
        n = iter->second.get();
      }
    }
    n->values.insert(value.second);
  }

  void erase(const K &key, const V &value) {
    node *n = this->at(key);
    if (n != nullptr) {
      n->values.erase(value);
    }
  }

  template <class F>
  void each(F &f, const K &key = K()) { // NOLINT
    node *n = this->at(key);
    if (n == nullptr) {
      return;
    }
    this->each(f, n);
  }

 private:
  node root;
};

#endif  // SRC_TRIE_MAP_H_
