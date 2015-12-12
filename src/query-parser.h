#include <string>
#include "query.h"

#ifndef SRC_QUERY_PARSER_H_
#define SRC_QUERY_PARSER_H_

class QueryParser {
 private:
    virtual Query parseWQuery(const std::string &args);

    virtual Query parseQuery(const std::string &args);

 public:
    virtual Query parse(const std::string &query);
};

#endif  // SRC_QUERY_PARSER_H_
