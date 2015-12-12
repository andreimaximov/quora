#include <string>
#include <vector>
#include <memory>
#include "query-parser.h"
#include "memory-service.h"

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

enum COMMAND {
    ADD, DEL, QUERY, WQUERY
};

class Controller {
 private:
    std::shared_ptr<QueryParser> queryParser;

    std::shared_ptr<MemoryService> memoryService;

    virtual void add(const std::string &command);

    virtual void del(const std::string &command);

    virtual std::vector<std::string> query(const std::string &command);

 public:
    static const std::string ADD_CMD;

    static const std::string DEL_CMD;

    static const std::string QUERY_CMD;

    static const std::string WQUERY_CMD;

    explicit Controller(
        std::shared_ptr<QueryParser> queryParser,
        std::shared_ptr<MemoryService> memoryService);

    virtual void call(const std::string &command);
};

#endif  // SRC_CONTROLLER_H_
