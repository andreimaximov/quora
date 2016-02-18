#include <algorithm>
#include "trie.h"

void Trie::insert(const std::string &str) {
    Node *node = &(this->root);
    for (const char &c : str) {
        node = &(node->children[c]);
    }
    this->depth = std::max(this->depth, str.length());
}

bool Trie::contains(const std::string &str) const {
    const Node *node = &(this->root);
    for (const char &c : str) {
        auto iter = node->children.find(c);
        if (iter == node->children.end()) {
            return false;
        }
        node = &(iter->second);
    }
    return true;
}

void Trie::tails(
    const Node &node,
    std::vector<std::string> &tails,
    std::vector<char> &chars,
    size_t i) const {
    if (node.children.empty()) {
        tails.emplace_back(chars.begin(), chars.begin() + i);
        return;
    }
    for (const auto &iter : node.children) {
        chars[i] = iter.first;
        this->tails(iter.second, tails, chars, i + 1);
    }
}

std::vector<std::string> Trie::tails() const {
    std::vector<std::string> result;
    std::vector<char> chars(this->depth);
    this->tails(this->root, result, chars, 0);
    return result;
}
