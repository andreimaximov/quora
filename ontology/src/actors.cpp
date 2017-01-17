#include <stack>
#include "actors.hpp"

//
// Query
//

std::istream& operator>>(std::istream &is, Query &query) {
  is >> query.topic;
  is.get();
  std::getline(is, query.prefix);
  return is;
}

//
// Question
//

bool Question::operator<(const Question& other) const {
  return topic < other.topic;
}

//
// Ontology
//

Ontology parse(int N, std::istream& is) {
  Ontology ontology;

  std::stack<std::string> tree;
  std::string token;
  std::string last;
  int depth = 0;
  int i = 0;

  while (depth > 0 || N > 0) {
    is >> token;


    if (token == "(") {
      tree.push(last);
      last.clear();
      depth++;
    } else {
      if (last.size() > 0) {
        ontology[last].hi = i;
        last.clear();
      }

      if (token == ")") {
        ontology[tree.top()].hi = i;
        tree.pop();
        depth--;
      } else {
        ontology[token].lo = ++i;
        last = std::move(token);
        N--;
      }
    }
  }

  return ontology;
}
