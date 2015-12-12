#include <string>
#include <vector>
#include "query-parser.h"

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

enum COMMAND {
    ADD, DEL, QUERY, WQUERY
};

class Controller {
 private:
    QueryParser queryParser;

    virtual void add(const std::string &command);

    virtual void del(const std::string &command);

    virtual std::vector<std::string> query(const std::string &command);

 public:
    static const std::string ADD_CMD;

    static const std::string DEL_CMD;

    static const std::string QUERY_CMD;

    static const std::string WQUERY_CMD;

    explicit Controller(QueryParser QueryParser);

    virtual void call(const std::string &command);
};

#endif  // SRC_CONTROLLER_H_
