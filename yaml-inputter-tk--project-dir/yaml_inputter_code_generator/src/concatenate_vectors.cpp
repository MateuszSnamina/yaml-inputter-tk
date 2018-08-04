#include<concatenate_vectors.hpp>

std::vector<std::string> concatenate_vectors(
        const std::vector<std::string>& A,
        const std::vector<std::string>& B) {
    std::vector<std::string> AB;
    AB.reserve(A.size() + B.size()); // preallocate memory
    AB.insert(AB.end(), A.begin(), A.end());
    AB.insert(AB.end(), B.begin(), B.end());
    return AB;
}

