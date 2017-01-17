#include <string>
#include <vector>
#include <utility>
#include "actors.hpp"

#ifndef TRIE_HPP_
#define TRIE_HPP_

//
// Trie of question body prefixes implemented as a TST.
//
class Trie {
 private:
  struct Node {
    explicit Node(char key);

    //
    // Delete copy constructor and assignment operator to avoid bad behavior.
    //

    Node(const Node& other) = delete;

    void operator=(const Node& other) = delete;

    ~Node();

    char key;

    int count = 0;

    //
    // Each (x, count) pair represents the number of questions belonging to a
    // topic t such that lo(t) <= x.
    //
    // Questions are expected to be inserted in ORDER OF INCREASING TOPIC so
    // that each insertion is O(1) time! Insertion of questions in any other
    // order will result in unpredictable results.
    //
    std::vector<std::pair<int, int>> partials;

    Node* left = nullptr;

    Node* mid = nullptr;

    Node* right = nullptr;
  };

  Node root;

  const Ontology& ontology;

  //
  // Inserts the question into the trie rooted at the given node starting
  // at position i in the body.
  //
  Node* insert(const Question& question, int i, Node* node);

  //
  // Returns the node where the prefix terminates or nullptr if the prefix is
  // not in the trie.
  //
  const Node* find(const std::string& prefix) const;

 public:
  //
  // Creates a trie with the ontology.
  //
  explicit Trie(const Ontology& ontology);

  //
  // Inserts a question into the trie. Questions are expected to be inserted in
  // ORDER OF INCREASING TOPIC so that each insertion is O(1) time! Insertion
  // of questions in any other order will result in unpredictable results.
  //
  void insert(const Question& question);

  //
  // Returns the number of questions inserted into the trie that match the
  // query.
  //
  int count(const Query& query) const;
};

#endif  // TRIE_HPP_
