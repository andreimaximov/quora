#include <istream>
#include <string>
#include "query.h"

#ifndef SRC_QUERY_PARSER_H_
#define SRC_QUERY_PARSER_H_

class QueryParser {
 private:
  void applyBoosts(std::istream& in, Query& query) const; //NOLINT

  void applyTokens(std::istream& in, Query& query) const; // NOLINT
 public:
  static const std::string TYPE_QUERY;

  static const std::string TYPE_WQUERY;

  Query parse(Query::Type type, std::istream& in) const; // NOLINT
};

#endif  // SRC_QUERY_PARSER_H_
