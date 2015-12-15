#include <string>
#include <vector>
#include <unordered_map>

#ifndef SRC_TRIE_H_
#define SRC_TRIE_H_

class Trie {
 public:
    struct Node {
        std::unordered_map<char, Node*> children;
    };

    void insert(const std::string &str);

    bool contains(const std::string &str) const;

    std::vector<std::string> tails();

 private:
    Node root;

    unsigned int depth;

    unsigned int width;

    void tails(
        const Node *node,
        std::vector<std::string> &tails, // NOLINT
        std::vector<char> &chars); // NOLINT
};

#endif  // SRC_TRIE_H_
