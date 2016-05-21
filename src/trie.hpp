#include <unordered_set>
#include <memory>

#ifndef SRC_TRIE_HPP_
#define SRC_TRIE_HPP_

//
// Ternary Search Trie implementation of a trie. Each inserted key has a
// corresponding value which is stored in the values set of each middle node
// along the path to the terminal node of each key.
//
// Allows the following operations where N is the length of the key:
//
// insert : O(N)
// erase : O(N)
// find : O(N)
//
template <class Key, class Value>
class trie {
 private:
  class node {
   public:
    typedef std::unique_ptr<node> u_ptr;

    typedef typename Key::value_type key_type;

    u_ptr left;

    u_ptr mid;

    u_ptr right;

    key_type key;

    std::unordered_set<Value> values;

    explicit node(const key_type& key) : key(key) {
    }

    node(const node&) = delete;

    node& operator=(const node&) = delete;

    //
    // Returns a bool if this is an empty node and false otherwise. The node is
    // empty if it is not useful for representing any information such as child
    // nodes or set values.
    //
    bool empty() {
      return this->values.empty() && !this->left && !this->mid && !this->right;
    }
  };

  typedef typename node::u_ptr node_ptr;

  typedef typename Key::size_type key_size;

 public:
  typedef std::pair<Key, Value> value_type;

 private:
  //
  // Inserts the value into the trie at the specified node begining at index i
  // of the key.
  //
  void insert(node_ptr& root, const value_type& value, key_size i) { // NOLINT
    auto key = value.first[i];
    if (!root) {
      root.reset(new node(key));
    }
    if (key < root->key) {
      this->insert(root->left, value, i);
    } else if (key > root->key) {
      this->insert(root->right, value, i);
    } else if (i < value.first.size() - 1) {
      root->values.insert(value.second);
      this->insert(root->mid, value, i + 1);
    } else {
      root->values.insert(value.second);
    }
  }

  //
  // Erases the key/value pair from the trie rooted at the specified node.
  // key[i] is compared at the specified node to determine the traversal
  // direction to reach the terminal node of this key.
  //
  void erase(node_ptr& root, const value_type& value, key_size i) { // NOLINT
    if (!root) {
      return;
    }
    auto k = value.first[i];
    if (k < root->key) {
      this->erase(root->left, value, i);
    } else if (k > root->key) {
      this->erase(root->right, value, i);
    } else if (i < value.first.size() - 1) {
      root->values.erase(value.second);
      this->erase(root->mid, value, i + 1);
    } else {
      root->values.erase(value.second);
    }
    if (root->empty()) {
      root.reset(nullptr);
    }
  }

  //
  // Returns a reference to the pointer where the key terminates. i is used to
  // compare key[i] to the current node and decide which branch to continue
  // traversing. The returned reference may be an empty std::unique_ptr<node>.
  //
  const node_ptr& find(const node_ptr& root, const Key& key, key_size i) const {
    if (!root || key.size() == 0) {
      return root;
    }
    auto k = key[i];
    if (k < root->key) {
      return this->find(root->left, key, i);
    } else if (k > root->key) {
      return this->find(root->right, key, i);
    } else if (i < key.size() - 1) {
      return this->find(root->mid, key, i + 1);
    } else {
      return root;
    }
  }

 public:
  trie() : root(nullptr) {
  }

  trie(const trie&) = delete;

  trie& operator=(const trie&) = delete;

  //
  // Inserts the value into every set along the branch representing the
  // insertion key.
  //
  void insert(const value_type& value) {
    this->insert(this->root, value, 0);
  }

  //
  // Returns a reference to the set of values where this key terminates. If this
  // key does not exist, an empty set reference is returned.
  //
  const std::unordered_set<Value>& operator[] (const Key& key) {
    const node_ptr& node = this->find(this->root, key, 0);
    if (!node) {
      return this->empty;
    }
    return node->values;
  }

  //
  // Erase the key/value pair from the trie and erases the value from every set
  // along the branch representing the key.
  //
  void erase(const value_type& value) {
    this->erase(this->root, value, 0);
  }

 private:
  //
  // Initially empty root node of the TST
  //
  node_ptr root;

  //
  // The empty set returned by operator[] for non existent keys
  //
  std::unordered_set<Value> empty;
};

#endif  // SRC_TRIE_HPP_
