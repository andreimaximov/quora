#include <sstream>
#include <vector>
#include <algorithm>
#include "controller.hpp"
#include "item.hpp"
#include "split.hpp"

const std::string Controller::COMMAND_ADD = "ADD";

const std::string Controller::COMMAND_DEL = "DEL";

const std::string Controller::COMMAND_QUERY = "QUERY";

const std::string Controller::COMMAND_WQUERY = "WQUERY";

Controller::Controller(
  QueryParser& queryParser,
  Typeahead& typeahead,
  std::ostream& os) :
  queryParser(queryParser),
  typeahead(typeahead),
  out(os) {
}

void Controller::execute(const std::string& statement) {
  std::istringstream in(statement);
  std::string action;
  in >> action;

  if (action == Controller::COMMAND_ADD) {
    this->add(in);
  } else if (action == Controller::COMMAND_DEL) {
    this->del(in);
  } else if (action == Controller::COMMAND_QUERY) {
    this->query(Query::Type::STANDARD, in);
  } else if (action == Controller::COMMAND_WQUERY) {
    this->query(Query::Type::BOOSTED, in);
  } else {
    throw std::invalid_argument("Invalid command!");
  }
}

void Controller::add(std::istream& in) {
  Item item;
  std::string token;

  // Parse type
  in >> token;
  item.type = Item::stotype(token);

  // Parse ID
  in >> item.id;

  // Parse score
  in >> token;
  item.score = std::stof(token);

  // Parse tokens and transform to lowercase
  item.tokens = split(in);
  for (auto it = item.tokens.begin(); it != item.tokens.end(); ++it) {
    std::transform(it->begin(), it->end(), it->begin(), ::tolower);
  }

  this->typeahead.add(item);
}

void Controller::del(std::istream& in) {
  std::string id;
  in >> id;
  this->typeahead.del(id);
}

void Controller::query(Query::Type type, std::istream& in) {
  Query query = this->queryParser.parse(type, in);
  std::vector<const Item*> results = this->typeahead.query(query);

  std::string separator("");
  for (const Item* item : results) {
    this->out << separator << item->id;
    separator = " ";
  }
  this->out << std::endl;
}
