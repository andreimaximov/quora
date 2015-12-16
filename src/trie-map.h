#include <string>
#include <unordered_set>
#include <unordered_map>
#include <stack>

#ifndef SRC_TRIE_MAP_H_
#define SRC_TRIE_MAP_H_

template <class E>
class TrieMap {
 private:
    struct Node {
        std::unordered_set<E> elements;

        std::unordered_map<char, Node> children;
    };

    Node* getPrefixNode(const std::string &str) {
        size_t i = 0;
        Node *node = &(this->root);
        while (i < str.length()) {
            char c = str.at(i);
            auto found = node->children.find(c);
            if (found == node->children.end()) {
                return nullptr;
            }
            node = &(found->second);
            i++;
        }
        return node;
    }

 public:
    void insert(const std::string &str, const E &val) {
        Node *node = &(this->root);
        size_t i = 0;
        while (i < str.length()) {
            char c = str.at(i);
            node = &(node->children[c]);
            i++;
        }
        node->elements.insert(val);
    }

    void erase(const std::string &str, const E &val) {
        Node *node = this->getPrefixNode(str);
        if (node != nullptr) {
            node->elements.erase(val);
        }
    }

    template <class F>
    void traverse(F &f, const std::string &str = "") { // NOLINT
        Node *root = this->getPrefixNode(str);
        if (root == nullptr) {
            return;
        }

        std::stack<Node*> nodes;
        nodes.push(root);

        while (nodes.size() > 0) {
            Node *node = nodes.top();
            nodes.pop();
            for (const E &elem : node->elements) {
                f(elem);
            }
            for (auto &pair : node->children) {
                nodes.push(&pair.second);
            }
        }
    }

 private:
    Node root;
};

#endif  // SRC_TRIE_MAP_H_
