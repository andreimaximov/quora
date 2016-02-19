#include <istream>
#include "query.h"

#ifndef SRC_QUERY_PARSER_H_
#define SRC_QUERY_PARSER_H_

class QueryParser {
 private:
  void boost(std::istream &istream, Query &query); //NOLINT

  void buildTokens(std::istream &istream, Query &query); // NOLINT
 public:
  enum Type {
    QUERY, WQUERY
  };

  static const std::string TYPE_QUERY;

  static const std::string TYPE_WQUERY;

  Type type(const std::string &type);

  Query parse(const std::string &command);
};

#endif  // SRC_QUERY_PARSER_H_
