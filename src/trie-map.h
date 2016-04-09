#include <memory>

#ifndef SRC_TRIE_MAP_H_
#define SRC_TRIE_MAP_H_

template <class Key, class Value>
class trie_map {
 private:
  class node {
   public:
    typedef std::unique_ptr<node> u_ptr;

    typedef std::unique_ptr<Value> value_type;

    typedef typename Key::value_type key_type;

    u_ptr left;

    u_ptr mid;

    u_ptr right;

    key_type key;

    value_type value;

    explicit node(const key_type &key) : key(key), value(nullptr) {
    }

    node(const node& other) = delete;

    node& operator=(const node &other) = delete;

    bool empty() {
      return !this->value && !this->left && !this->mid && !this->right;
    }
  };

  typedef typename node::u_ptr node_ptr;

  typedef typename Key::size_type key_size;

 public:
  typedef std::pair<Key, Value> value_type;

 private:
  node_ptr& insert(node_ptr &root, const value_type &value, key_size i, // NOLINT
      const bool &overwrite) {
    auto k = value.first[i];
    if (!root) {
      root.reset(new node(k));
    }
    if (k < root->key) {
      return this->insert(root->left, value, i, overwrite);
    } else if (k > root->key) {
      return this->insert(root->right, value, i, overwrite);
    } else if (i < value.first.size() - 1) {
      return this->insert(root->mid, value, i + 1, overwrite);
    }
    if (!root->value || overwrite) {
      root->value.reset(new Value(value.second));
    }
    return root;
  }

  void erase(node_ptr &root, const Key &key, key_size i) { // NOLINT
    if (!root) {
      return;
    }
    auto k = key[i];
    if (k < root->key) {
      this->erase(root->left, key, i);
    } else if (k > root->key) {
      this->erase(root->right, key, i);
    } else if (i < key.size() - 1) {
      this->erase(root->mid, key, i + 1);
    } else {
      root->value.reset(nullptr);
    }
    if (root->empty()) {
      root.reset(nullptr);
    }
  }

  const node_ptr& at(const node_ptr &root, const Key &key, key_size i) const { // NOLINT
    if (!root || key.size() == 0) {
      return root;
    }
    auto k = key[i];
    if (k < root->key) {
      return this->at(root->left, key, i);
    } else if (k > root->key) {
      return this->at(root->right, key, i);
    } else if (i < key.size() - 1) {
      return this->at(root->mid, key, i + 1);
    } else {
      return root;
    }
  }

  template <class Consumer>
  void each(Consumer &consumer, const node_ptr &root) const { // NOLINT
    if (!root) {
      return;
    }
    if (root->value) consumer(*root->value);
    this->each(consumer, root->left);
    this->each(consumer, root->mid);
    this->each(consumer, root->right);
  }

 public:
  trie_map() : root(nullptr) {
  }

  trie_map(const trie_map& other) = delete;

  trie_map& operator=(const trie_map &other) = delete;

  void insert(const value_type &value) {
    this->insert(this->root, value, 0, true);
  }

  Value& operator[] (const Key &key) {
    value_type value(key, Value());
    return *this->insert(this->root, value, 0, false)->value;
  }

  void erase(const Key &key) {
    this->erase(this->root, key, 0);
  }

  bool contains(const Key &key) const {
    const node_ptr& node = this->at(this->root, key, 0);
    return node.get() != nullptr; // NOLINT
  }

  template <class Consumer>
  void each(Consumer &consumer, const Key &key = Key()) const { // NOLINT
    const node_ptr& node = this->at(this->root, key, 0);
    if (node == nullptr) {
      return;
    }
    if (node->value) consumer(*node->value);
    this->each(consumer, node->mid);
  }

 private:
  node_ptr root;
};

#endif  // SRC_TRIE_MAP_H_
