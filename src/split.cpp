#include <iterator>
#include "split.h"

std::vector<std::string> split(std::istream& in) { // NOLINT
  std::istream_iterator<std::string> begin(in), end;
  return std::vector<std::string>(begin, end);
}
