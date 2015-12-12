#include <vector>
#include <sstream>

std::vector<std::string> split(
    const std::string &src,
    char delim,
    int limit = -1
) {
    std::vector<std::string> tokens;
    std::stringstream stream(src);
    std::string token;
    while (--limit != 0 && getline(stream, token, delim)) {
        tokens.push_back(token);
    }
    if (getline(stream, token)) {
        tokens.push_back(token);
    }
    return tokens;
}
