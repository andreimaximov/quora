#include <string>
#include <istream>
#include "query.h"

#ifndef SRC_QUERY_PARSER_H_
#define SRC_QUERY_PARSER_H_

class QueryParser {
 private:
  void boost(std::istream &istream, Query &query) const; //NOLINT

  void buildTokens(std::istream &istream, Query &query) const; // NOLINT
 public:
  enum Type {
    QUERY, WQUERY
  };

  static const std::string TYPE_QUERY;

  static const std::string TYPE_WQUERY;

  Type type(const std::string &type) const;

  Query parse(const std::string &command) const;
};

#endif  // SRC_QUERY_PARSER_H_
