#include <istream>
#include "query.h"

#ifndef SRC_QUERY_PARSER_H_
#define SRC_QUERY_PARSER_H_

class QueryParser {
 private:
    Query parseWQuery(std::istream &stream); //NOLINT

    Query parseQuery(std::istream &stream); //NOLINT

 public:
    virtual Query parse(const std::string &query);
};

#endif  // SRC_QUERY_PARSER_H_
