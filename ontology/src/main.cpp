#include <string>
#include <vector>
#include <iostream>
#include "actors.hpp"
#include "trie.hpp"

//
// Reads an int from stdin and discards the rest of the line.
//
int get_int() {
  int i;
  std::cin >> i;
  std::string line;
  std::getline(std::cin, line);
  return i;
}

int main() {
  // Build the ontology tree.
  int N = get_int();
  Ontology ontology = parse(N, std::cin);

  // Load questions.
  int M = get_int();
  std::vector<Question> questions(M);

  for (int i = 0; i < M; i++) {
    std::string topic;
    std::cin >> topic;
    topic.erase(topic.size() - 1);
    questions[i].topic = ontology[topic].lo;

    std::cin.get();
    std::getline(std::cin, questions[i].body);
  }

  // Populate the trie.
  sort(questions.begin(), questions.end());

  Trie trie(ontology);
  for (const Question& question : questions) {
    trie.insert(question);
  }

  // Query the ontology.
  int K = get_int();
  while (K-- > 0) {
    Query query;
    std::cin >> query;
    std::cout << trie.count(query) << '\n';
  }

  return 0;
}
