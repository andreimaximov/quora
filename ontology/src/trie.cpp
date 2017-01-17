#include <algorithm>
#include "trie.hpp"

//
// Trie::Node
//

Trie::Node::Node(char key) : key(key) {
  // Base case/sentinel that does not conflict because lo(topic) > 0.
  partials.push_back({0, 0});
}

Trie::Node::~Node() {
  delete left;
  delete mid;
  delete right;
}

//
// Trie
//

Trie::Trie(const Ontology& ontology) : ontology(ontology), root('\0') {
}

Trie::Node* Trie::insert(const Question& question, int i, Node* node) {
  // Check if we have fully inserted the question body into the trie.
  if (i == question.body.size()) {
    return node;
  }

  char key = question.body[i];
  if (node == nullptr) {
    node = new Node {key};
  }

  // Try and insert the current key into the trie.
  if (key < node->key) {
    node->left = insert(question, i, node->left);
  } else if (key > node->key) {
    node->right = insert(question, i, node->right);
  } else {
    // This is where we update the (x, count) pairs - see trie.hpp for details
    // on what this means. We can do this in O(1) time only if the questions are
    // beign inserted in order of increasing topic ID because then we can easily
    // accumulate the count from left to right.
    auto& tail = node->partials.back();
    if (tail.first != question.topic) {
      node->partials.push_back({question.topic, tail.second});
    }
    node->partials.back().second++;

    node->mid = insert(question, i + 1, node->mid);
  }

  return node;
}

const Trie::Node* Trie::find(const std::string& prefix) const {
  const Node* last = nullptr;
  const Node* node = root.mid;
  auto it = prefix.begin();

  while (node != nullptr && it != prefix.end()) {
    if (*it < node->key) {
      node = node->left;
    } else if (*it > node->key) {
      node = node->right;
    } else {
      ++it;
      last = node;
      node = node->mid;
    }
  }

  return (it == prefix.end()) ? last : nullptr;
}

void Trie::insert(const Question& question) {
  root.mid = insert(question, 0, root.mid);
}

int Trie::count(const Query& query) const {
  // Begin by checking if the query prefix is in the trie.
  auto node = find(query.prefix);
  if (node == nullptr) {
    return 0;
  }

  // Now we have a node that is the root of a tree containing all questions
  // with the query prefix. We just need to count the subset of these which
  // are in the query topic.
  //
  // How can we do this efficiently? Well, we know that for all topics x,
  // lo(x) >= lo(parent(x)), hi(x) <= hi(parent(x)), and lo(x) <= hi(x). Thus
  // we just need count all questions with a topic in the range
  // [topic.lo, topic.hi]!
  const Topic& topic = ontology.at(query.topic);

  //
  // This is easy to do since at each node we have a list of (x, count) pairs
  // representing the number of questions belonging to a topic t such that
  // lo(t) <= x. We just need to calculate count(topic.hi) - count(topic.lo - 1)
  // via binary search!
  //
  auto begin = std::lower_bound(node->partials.begin(),
                                node->partials.end(),
                                std::make_pair(topic.lo, 0));

  int left = (--begin)->second;

  auto end = std::lower_bound(node->partials.begin(),
                              node->partials.end(),
                              std::make_pair(topic.hi + 1, 0));

  int right = (--end)->second;

  return right - left;
}
