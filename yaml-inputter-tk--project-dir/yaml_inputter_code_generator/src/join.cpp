#include<join.hpp>

std::string join(
        const std::vector<std::string> &strings,
        const std::string & glue) {
    if (strings.empty())
        return "";
    std::string result = strings[0];
    for (unsigned i = 1; i < strings.size(); i++) {
        result += glue + strings[i];
    }
    return result;
}