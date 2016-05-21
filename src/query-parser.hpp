#include <istream>
#include <string>
#include "query.hpp"

#ifndef SRC_QUERY_PARSER_HPP_
#define SRC_QUERY_PARSER_HPP_

class QueryParser {
 private:
  //
  // Parses the istream for Item::Type or Item ID boosts and applies them to the
  // Query object.
  //
  void applyBoosts(std::istream& in, Query& query) const; //NOLINT

  //
  // Parses the istream for search tokens and adds them to the Query object.
  //
  void applyTokens(std::istream& in, Query& query) const; // NOLINT
 public:
  static const std::string TYPE_QUERY;

  static const std::string TYPE_WQUERY;

  //
  // Parses the istream query which is expected to contain a query statement of
  // the specified type and returns a Query object.
  //
  Query parse(Query::Type type, std::istream& in) const; // NOLINT
};

#endif  // SRC_QUERY_PARSER_HPP_
