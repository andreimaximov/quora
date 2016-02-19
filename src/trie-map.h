#include <string>
#include <unordered_set>
#include <unordered_map>
#include <stack>

#ifndef SRC_TRIE_MAP_H_
#define SRC_TRIE_MAP_H_

template <class V>
class TrieMap {
 private:
  struct Node {
    std::unordered_set<V> values;

    std::unordered_map<char, Node> children;
  };

  Node* at(const std::string &key) {
    Node *node = &(this->root);
    for (const char &c : key) {auto found = node->children.find(c);
      if (found == node->children.end()) {
        return nullptr;
      }
      node = &(found->second);
    }
    return node;
  }

  template <class F>
  void each(F &f, const Node &root) { // NOLINT
    for (const V &value : root.values) {
      f(value);
    }
    for (const auto &it : root.children) {
      this->each(f, it.second);
    }
  }

 public:
  void insert(const std::string &key, const V &value) {
    Node *node = &(this->root);
    for (const char &c : key) {
      node = &(node->children[c]);
    }
    node->values.insert(value);
  }

  void erase(const std::string &key, const V &value) {
    Node *node = this->at(key);
    if (node != nullptr) {
      node->values.erase(value);
    }
  }

  template <class F>
  void each(F &f, const std::string &key = "") { // NOLINT
    Node *root = this->at(key);
    if (root == nullptr) {
      return;
    }
    this->each(f, *root);
  }

 private:
  Node root;
};

#endif  // SRC_TRIE_MAP_H_
