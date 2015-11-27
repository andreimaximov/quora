#include <string>
#include <map>
#include "query.h"

#ifndef SRC_QUERY_PARSER_H_
#define SRC_QUERY_PARSER_H_

class QueryParser {
 private:
    std::map<std::string, ItemType>* typeMap;

    virtual std::vector<std::string>* split(std::string text, char delimeter);

    virtual Query* parseWQuery(std::string* args);

    virtual Query* parseQuery(std::string* args);

 public:
    explicit QueryParser(std::map<std::string, ItemType>* typeMap);

    virtual Query* parse(std::string* query);
};

#endif  // SRC_QUERY_PARSER_H_
