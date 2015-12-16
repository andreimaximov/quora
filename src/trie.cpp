#include <algorithm>
#include "trie.h"

void Trie::insert(const std::string &str) {
    size_t i = 0;
    Node *node = &(this->root);
    while (i < str.length()) {
        char c = str.at(i);
        node = &(node->children[c]);
        i++;
    }
    this->depth = std::max(this->depth, i);
}

bool Trie::contains(const std::string &str) const {
    size_t i = 0;
    const Node *node = &(this->root);
    while (i < str.length()) {
        char c = str.at(i);
        auto found = node->children.find(c);
        if (found == node->children.end()) {
            return false;
        }
        node = &(found->second);
        i++;
    }
    return true;
}

void Trie::tails(
    const Node &node,
    std::vector<std::string> &tails,
    std::vector<char> &chars,
    size_t i) const {
    if (node.children.size() == 0) {
        std::string str(chars.begin(), chars.begin() + i);
        tails.push_back(std::move(str));
        return;
    }
    for (auto &pair : node.children) {
        chars[i] = pair.first;
        this->tails(pair.second, tails, chars, i + 1);
    }
}

std::vector<std::string> Trie::tails() const {
    std::vector<std::string> result;
    std::vector<char> chars(this->depth);
    this->tails(this->root, result, chars, 0);
    return result;
}
