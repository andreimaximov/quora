#include <string>
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

    std::ostream &out;

    void add(const std::string &command);

    void del(const std::string &command);

    void query(const std::string &command);

 public:
    static const std::string ADD_CMD;

    static const std::string DEL_CMD;

    static const std::string QUERY_CMD;

    static const std::string WQUERY_CMD;

    explicit Controller(
        std::shared_ptr<QueryParser> queryParser,
        std::shared_ptr<MemoryService> memoryService,
        std::ostream &os); // NOLINT

    void call(const std::string &command);
};

#endif  // SRC_CONTROLLER_H_
