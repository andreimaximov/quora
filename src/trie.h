#include <string>
#include <vector>
#include <unordered_map>

#ifndef SRC_TRIE_H_
#define SRC_TRIE_H_

class Trie {
 public:
    void insert(const std::string &str);

    bool contains(const std::string &str) const;

    std::vector<std::string> tails() const;

 private:
    struct Node {
        std::unordered_map<char, Node> children;
    };

    Node root;

    size_t depth = 0;

    void tails(
        const Node &node,
        std::vector<std::string> &tails, // NOLINT
        std::vector<char> &chars, // NOLINT
        size_t i) const;
};

#endif  // SRC_TRIE_H_
