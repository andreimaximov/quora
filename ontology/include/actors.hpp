#include <string>
#include <unordered_map>
#include <istream>

#ifndef ACTORS_HPP_
#define ACTORS_HPP_

//
// Topic with a trie of question prefixes and children.
//
struct Topic {
  int lo;

  int hi;
};

//
// Query with a topic and prefix string to match against.
//
struct Query {
  std::string topic;

  std::string prefix;
};

//
// Parses a query from an input stream.
//
std::istream& operator>>(std::istream &is, Query &query);

//
// Question with a body and associated topic.
//
struct Question {
  int topic;

  std::string body;

  bool operator<(const Question& other) const;
};

//
// Ontologies are just maps from titles to topic representations.
//
using Ontology = std::unordered_map<std::string, Topic>;

//
// Parses a topics tree stream to build an ontology. We can perform a Euler
// tour starting at the root to apply a range [lo, hi] to each topic such
// that lo(x) >= lo(parent(x)), hi(x) <= hi(parent(x)), and lo(x) <= hi(x).
//
Ontology parse(int N, std::istream& is);

#endif  // ACTORS_HPP_
