#include<classes_kit/read_fields.hpp>
#include<classes_kit/make_field.hpp>

void read_fields(
        const YAML::Node & node,
        std::vector<std::shared_ptr<Field>> & fields) {
    
    if (node.IsScalar()) {
        std::string error = "[ERROR] [NodeTypeError] Unexpected scalar-yaml-node.";
        std::string prompt = "Expected optional sequence-yaml-node with fields definitions.";
        throw std::runtime_error(error + "\n" + prompt);
    }
    if (node.IsMap()) {
        std::string error = "[ERROR] [NodeTypeError] Unexpected map-yaml-node.";
        std::string prompt = "Expected optional sequence-yaml-node with fields definitions.";
        throw std::runtime_error(error + "\n" + prompt);
    }
    
    const unsigned n_fields = node.IsSequence() ? node.size() : 0;
    fields.clear();    
    fields.reserve(n_fields);
    for (unsigned i = 0; i < n_fields; i++) {
        try {
            std::shared_ptr<Field> f = make_field(node[i]);
            fields.push_back(f);
        } catch (const std::runtime_error& e) {
            const std::string where = "field no " + std::to_string(i);
            const std::string message = "[BACKTRACE] Error occurred when read " + where + ".";
            throw std::runtime_error(message + "\n" + e.what());
        }
    }
}