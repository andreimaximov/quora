#include <algorithm>
#include "trie.h"

void Trie::insert(const std::string &str) {
    size_t i = 0;
    Node *node = &(this->root);
    while (i < str.length()) {
        const char &c = str.at(i);
        if (node->children.find(c) == node->children.end()) {
            node->children[c] = new Node();
            this->width += (1 ? i == str.length() - 1 : 0);
        }
        node = node->children[c];
        i++;
    }
    this->depth = std::max(this->depth, (unsigned int) i - 1);
}

bool Trie::contains(const std::string &str) const {
    size_t i = 0;
    const Node *node = &(this->root);
    while (i < str.length()) {
        const char &c = str.at(i);
        if (node->children.find(c) == node->children.end()) {
            return false;
        }
        node = node->children.at(c);
        i++;
    }
    return true;
}

void Trie::tails(
    const Node *node,
    std::vector<std::string> &tails,
    std::vector<char> &chars) {
    if (node->children.size() == 0) {
        std::string str(chars.begin(), chars.end());
        tails.push_back(std::move(str));
        return;
    }
    chars.push_back('\0');
    size_t i = chars.size() - 1;
    for (const std::pair<char, Trie::Node*> &pair : node->children) {
        chars[i] = pair.first;
        this->tails(pair.second, tails, chars);
    }
    chars.pop_back();
}

std::vector<std::string> Trie::tails() {
    std::vector<std::string> result;
    result.reserve(this->width);

    std::vector<char> chars;
    chars.reserve(this->depth);

    this->tails(&(this->root), result, chars);
    return result;
}
