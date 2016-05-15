#include <istream>
#include <string>
#include "query-parser.h"
#include "memory-service.h"
#include "query.h"

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

class Controller {
 private:
  QueryParser& queryParser;

  MemoryService& memoryService;

  std::ostream& out;

  void add(std::istream& in); // NOLINT

  void del(std::istream& in); // NOLINT

  void query(Query::Type type, std::istream& in); // NOLINT

 public:
  static const std::string COMMAND_ADD;

  static const std::string COMMAND_DEL;

  static const std::string COMMAND_QUERY;

  static const std::string COMMAND_WQUERY;

  Controller(
    QueryParser& queryParser, // NOLINT
    MemoryService& memoryService, // NOLINT
    std::ostream& os); // NOLINT

  void execute(const std::string& statement);
};

#endif  // SRC_CONTROLLER_H_
