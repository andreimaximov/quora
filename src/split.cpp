#include <vector>
#include <sstream>

std::vector<std::string>* split(const std::string &src, char delim) {
    std::vector<std::string>* tokens = new std::vector<std::string>();
    std::stringstream stream(src);
    std::string token;
    while (getline(stream, token, delim)) {
        tokens->push_back(token);
    }
    return tokens;
}
