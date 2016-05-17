#include <iostream>
#include <string>
#include "query-parser.hpp"
#include "typeahead.hpp"
#include "query.hpp"

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

class Controller {
 private:
  QueryParser& queryParser;

  Typeahead& typeahead;

  std::ostream& out;

  //
  // Adds the item encoded in the istream to the typeahead service.
  //
  void add(std::istream& in); // NOLINT

  //
  // Performs a deletion of the Item ID encoded in the istream from the
  // typeahead service.
  //
  void del(std::istream& in); // NOLINT

  //
  // Performs a query of the specified type on the typeahead service. The
  // body of the query is in the istream.
  //
  void query(Query::Type type, std::istream& in); // NOLINT

 public:
  static const std::string COMMAND_ADD;

  static const std::string COMMAND_DEL;

  static const std::string COMMAND_QUERY;

  static const std::string COMMAND_WQUERY;

  Controller(
    QueryParser& queryParser, // NOLINT
    Typeahead& typeahead, // NOLINT
    std::ostream& os); // NOLINT

  //
  // Parses the statement and executes an ADD, DEL, QUERY, or WQUERY on the
  // autocomplete service.
  //
  void execute(const std::string& statement);
};

#endif  // SRC_CONTROLLER_H_
