#include <string>
#include <unordered_set>
#include <unordered_map>
#include <ostream>

#ifndef SRC_TRIE_SET_H_
#define SRC_TRIE_SET_H_

template <class E>
struct TrieNode {
    char character;
    std::unordered_set<E> elements;
    std::unordered_map<char, TrieNode<E>> children;

    TrieNode() : character('\0') {
    }

    explicit TrieNode(char prefix) : character(prefix) {
    }

    friend std::ostream& operator<<(std::ostream &os, const TrieNode<E> &node) {
        os << "{[";
        bool first = true;
        for (const E &elem : node.elements) {
            if (!first) {
                os << ", ";
            }
            os << elem;
            first = false;
        }
        os << "] ";
        for (const std::pair<char, TrieNode<E>> &pair : node.children) {
            os << "{" << pair.first << ": " << pair.second << "}";
        }
        os << "}";
        return os;
    }
};

template <class E>
class TrieSet {
 private:
    TrieNode<E> root;

    size_t _size;

    bool add(TrieNode<E> &node, const std::string &key, int i, const E &val) { //NOLINT
        char c = key.at(i);
        if (node.children.find(c) == node.children.end()) {
            TrieNode<E> child(c);
            node.children.insert(std::make_pair(c, child));
        }
        TrieNode<E> &child = node.children[c];
        if (key.length() == i + 1) {
            if (child.elements.find(val) != child.elements.end()) {
                return false;
            }
            child.elements.insert(std::move(val));
            this->_size++;
            return true;
        }
        return this->add(child, key, i + 1, val);
    }

    std::unordered_set<E> get_prefix_set(
        TrieNode<E> &node, // NOLINT
        const std::string &key,
        int i) {
        char c = key.at(i);
        if (node.children.find(c) == node.children.end()) {
            return std::unordered_set<E>();
        }
        TrieNode<E> &child = node.children[c];
        if (key.length() == i + 1) {
            std::unordered_set<E> results = child.elements;
            this->merge_children(child, results);
            return results;
        }
        return this->get_prefix_set(child, key, i + 1);
    }

    void merge_children(const TrieNode<E> &node, std::unordered_set<E> &results) { // NOLINT
        for (const auto &pair : node.children) {
            results.insert(
                pair.second.elements.begin(),
                pair.second.elements.end());
            this->merge_children(pair.second, results);
        }
    }

    bool erase(TrieNode<E> &node, const std::string &key, int i, const E &val) { //NOLINT
        char c = key.at(i);
        if (node.children.find(c) == node.children.end()) {
            return false;
        }
        TrieNode<E> &child = node.children[c];
        if (key.length() == i + 1) {
            size_t erased = child.elements.erase(val);
            this->_size -= erased;
            return erased > 0;
        }
        return this->erase(child, key, i + 1, val);
    }

 public:
    bool add(const std::string &key, const E &val) {
        return this->add(this->root, key, 0, val);
    }

    std::unordered_set<E> get_prefix_set(const std::string &key) {
        return this->get_prefix_set(this->root, key, 0);
    }

    bool erase(const std::string &key, const E &val) {
        return this->erase(this->root, key, 0, val);
    }

    friend std::ostream& operator<<(std::ostream &os, const TrieSet<E> &trieSet) { // NOLINT
        return os << trieSet.root;
    }

    size_t size();
};

#include "trie-set.icpp"

#endif  // SRC_TRIE_SET_H_
