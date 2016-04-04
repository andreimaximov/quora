#include <sstream>
#include <iterator>
#include "split.h"

std::vector<std::string> split(const std::string &src, char delim) {
  std::istringstream buf(src);
  std::istream_iterator<std::string> begin(buf), end;
  return std::vector<std::string>(begin, end);
}
