#include <vector>

#ifndef SRC_SPLIT_H_
#define SRC_SPLIT_H_

std::vector<std::string> split(
  const std::string &src,
  char delim,
  int limit = -1
);

#endif  // SRC_SPLIT_H_
