#include <string>
#include <unordered_set>
#include <unordered_map>
#include <ostream>

#ifndef SRC_TRIE_SET_H_
#define SRC_TRIE_SET_H_

template <class E>
class TrieSet {
 public:
    struct Node {
        std::unordered_set<E> elements;
        std::unordered_map<char, Node*> children;
    };

    void insert(const std::string &str, const E &val) {
        Node *node = &(this->root);
        size_t i = 0;
        while (i < str.length()) {
            const char &c = str.at(i);
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new Node();
            }
            node = node->children[c];
            i++;
        }
        node->elements.insert(val);
    }

    Node* get_prefix_node(const std::string &str) {
        size_t i = 0;
        Node *node = &(this->root);
        while (i < str.length()) {
            const char &c = str.at(i);
            if (node->children.find(c) == node->children.end()) {
                return nullptr;
            }
            node = node->children[c];
            i++;
        }
        return node;
    }

    void erase(const std::string &str, const E &val) {
        Node *node = this->get_prefix_node(str);
        if (node != nullptr) {
            node->elements.erase(val);
        }
    }

 private:
    Node root;
};

#endif  // SRC_TRIE_SET_H_
