#include <string>
#include <memory>
#include "query-parser.h"
#include "memory-service.h"

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

class Controller {
 private:
    std::shared_ptr<QueryParser> queryParser;

    std::shared_ptr<MemoryService> memoryService;

    std::ostream &out;

    void add(const std::string &command);

    void del(const std::string &command);

    void query(const std::string &command);

 public:
    static const std::string CMD_ADD;

    static const std::string CMD_DEL;

    static const std::string CMD_QUERY;

    static const std::string CMD_WQUERY;

    explicit Controller(
        std::shared_ptr<QueryParser> queryParser,
        std::shared_ptr<MemoryService> memoryService,
        std::ostream &os); // NOLINT

    void call(const std::string &command);
};

#endif  // SRC_CONTROLLER_H_
