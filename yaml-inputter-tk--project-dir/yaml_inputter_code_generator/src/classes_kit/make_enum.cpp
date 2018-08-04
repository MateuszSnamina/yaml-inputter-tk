#include<classes_kit/make_enum.hpp>
#include<classes_kit/check_stray_fields.hpp>

std::shared_ptr<Enum> make_enum(const YAML::Node & node) {
    // *************************************************************************    
    if (!node.IsMap()) {
        std::string error1 = "[ERROR] [NodeTypeError]";
        std::string error2 = "Yaml::node defining the enum is not a map-yaml-node.";
        throw std::runtime_error(error1 + " " + error2);
    }
    // *************************************************************************    
    const std::set<std::string> valid_fields = {"cpp-name", "cpp-values"};
    check_stray_fields(valid_fields, node);
    // *************************************************************************    
    const YAML::Node cpp_name_node = node["cpp-name"];
    if (!cpp_name_node.IsDefined()) {
        std::string error1 = "[ERROR] [KeyError]";
        std::string error2 = "'cpp-name' sub-node is not defined.";
        throw std::runtime_error(error1 + " " + error2);
    }
    if (!cpp_name_node.IsScalar()) {
        std::string error1 = "[ERROR] [NodeTypeError]";
        std::string error2 = "'cpp-name' sub-node is not a scalar-yaml-node.";
        throw std::runtime_error(error1 + " " + error2);
    }
    const std::string cpp_name = cpp_name_node.as<std::string>();
    // *************************************************************************
    const YAML::Node cpp_values_node = node["cpp-values"];
    if (!cpp_values_node.IsDefined()) {
        std::string error1 = "[ERROR] [KeyError]";
        std::string error2 = "'cpp-values' sub-node is not defined.";
        throw std::runtime_error(error1 + " " + error2);
    }
    if (!cpp_values_node.IsSequence()) {
        std::string error1 = "[ERROR] [NodeTypeError]";
        std::string error2 = "'cpp-values' sub-node is not a sequence-yaml-node.";
        throw std::runtime_error(error1 + " " + error2);
    }
    const std::vector<std::string> cpp_values = cpp_values_node.as<std::vector < std::string >> (); // make throw TO DO try catch 
    // *************************************************************************
    return std::make_shared<Enum>(cpp_name, cpp_values);
}