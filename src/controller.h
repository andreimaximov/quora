#include <string>
#include <memory>
#include "query-parser.h"
#include "memory-service.h"

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

class Controller {
 private:
  const QueryParser &queryParser;

  MemoryService &memoryService;

  std::ostream &out;

  void add(const std::string &command);

  void del(const std::string &command);

  void query(const std::string &command);

 public:
  static const std::string CMD_ADD;

  static const std::string CMD_DEL;

  static const std::string CMD_QUERY;

  static const std::string CMD_WQUERY;

  Controller(
    const QueryParser &queryParser,
    MemoryService &memoryService, // NOLINT
    std::ostream &os); // NOLINT

    void call(const std::string &command);
};

#endif  // SRC_CONTROLLER_H_
