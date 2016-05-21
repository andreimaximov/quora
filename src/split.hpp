#include <istream>
#include <vector>

#ifndef SRC_SPLIT_HPP_
#define SRC_SPLIT_HPP_

//
// Returns a vector of strings in this istream split by whitespace or new lines.
//
std::vector<std::string> split(std::istream& in); // NOLINT

#endif  // SRC_SPLIT_HPP_
