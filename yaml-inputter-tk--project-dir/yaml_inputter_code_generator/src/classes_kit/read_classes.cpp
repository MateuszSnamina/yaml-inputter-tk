#include<classes_kit/read_classes.hpp>
#include<classes_kit/make_class.hpp>

void read_classes(
        const YAML::Node & node,
        const std::vector<std::string> & namesapces,
        std::vector<std::shared_ptr<Class>> & classes) {

    if (node.IsScalar()) {
        std::string error = "[ERROR] [NodeTypeError] Unexpected scalar-yaml-node.";
        std::string prompt = "Expected optional sequence-yaml-node with classes definitions.";
        throw std::runtime_error(error + "\n" + prompt);
    }
    if (node.IsMap()) {
        std::string error = "[ERROR] [NodeTypeError] Unexpected map-yaml-node.";
        std::string prompt = "Expected optional sequence-yaml-node with classes definitions.";
        throw std::runtime_error(error + "\n" + prompt);
    }

    const unsigned n_classes = node.IsSequence() ? node.size() : 0;
    classes.clear();
    classes.reserve(n_classes);
    for (unsigned i = 0; i < n_classes; i++) {
        try {
            std::shared_ptr<Class> c = make_class(node[i], namesapces);
            classes.push_back(c);
        } catch (const std::runtime_error& e) {
            const std::string where = "class no " + std::to_string(i);
            const std::string message = "[BACKTRACE] Error occurred when read " + where + ".";
            throw std::runtime_error(message + "\n" + e.what());
        }
    }
}

