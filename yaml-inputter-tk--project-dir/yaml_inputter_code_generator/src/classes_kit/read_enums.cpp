#include<classes_kit/read_enums.hpp>
#include<classes_kit/make_enum.hpp>

void read_enums(
        const YAML::Node & node,
        std::vector<std::shared_ptr<Enum>> &enums) {
    if (node.IsScalar()) {
        std::string error = "[ERROR] [NodeTypeError] Unexpected scalar-yaml-node.";
        std::string prompt = "Expected optional sequence-yaml-node with enums definitions.";
        throw std::runtime_error(error + "\n" + prompt);
    }
    if (node.IsMap()) {
        std::string error = "[ERROR] [NodeTypeError] Unexpected map-yaml-node.";
        std::string prompt = "Expected optional sequence-yaml-node with enums definitions.";
        throw std::runtime_error(error + "\n" + prompt);
    }
    
    const unsigned n_enums = node.IsSequence() ? node.size() : 0;
    enums.clear();    
    enums.reserve(n_enums);
    for (unsigned i = 0; i < n_enums; i++) {
        try {
            std::shared_ptr<Enum> f = make_enum(node[i]);
            enums.push_back(f);
        } catch (const std::runtime_error& e) {
            const std::string where = "enum no " + std::to_string(i);
            const std::string message = "[BACKTRACE] Error occurred when read " + where + ".";
            throw std::runtime_error(message + "\n" + e.what());
        }
    }
}
