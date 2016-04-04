#include <map>
#include <memory>

#ifndef SRC_TRIE_H_
#define SRC_TRIE_H_

template <typename V>
class trie {
 private:
  class node {
   public:
    typedef std::unique_ptr<node> u_ptr;

    typedef std::map<typename V::value_type, u_ptr> child_map;

    child_map children;

    node() {
    }

    node(const node& other) = delete;

    node& operator=(const node &other) = delete;
  };

  node root;

  size_t depth;

 public:
  trie() : depth(0) {
  }

  trie(const trie &other) = delete;

  trie& operator=(const trie &other) = delete;

  bool insert(const V &value)  {
    node *n = &this->root;
    bool inserted = false;
    for (const auto &v : value) {
      auto iter = n->children.find(v);
      if (iter == n->children.end()) {
        node *child = new node;
        n->children[v] = std::unique_ptr<node>(child);
        n = child;
        inserted = true;
      } else {
        n = iter->second.get();
      }
    }
    this->depth = std::max(this->depth, value.size());
    return inserted;
  }

  bool contains(const V &value) const {
    const node *n = &this->root;
    for (const auto &v : value) {
      auto iter = n->children.find(v);
      if (iter == n->children.end()) {
        return false;
      }
      n = iter->second.get();
    }
    return true;
  }
};

#endif  // SRC_TRIE_H_
