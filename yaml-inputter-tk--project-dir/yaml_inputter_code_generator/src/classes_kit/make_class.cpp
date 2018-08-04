#include<classes_kit/make_class.hpp>

#include<join.hpp>
#include<classes_kit/read_enums.hpp>
#include<classes_kit/read_classes.hpp>
#include<classes_kit/read_fields.hpp>
#include<classes_kit/check_stray_fields.hpp>

std::shared_ptr<Class> make_class(
        const YAML::Node & node,
        const std::vector<std::string> & namesapces) {
    // *************************************************************************
    if (!node.IsMap()) {
        std::string error = "[ERROR] [NodeTypeError] Yaml::node defining the class is not a map-yaml-node.";
        std::string prompt = "Such a node is required to be a map-yaml-node";
        throw std::runtime_error(error + " " + prompt);
    }
    // *************************************************************************    
    const std::set<std::string> valid_fields = {"name", "classes", "enums", "fields"};
    check_stray_fields(valid_fields, node);
    // *************************************************************************
    const YAML::Node name_node = node["name"];
    if (!name_node.IsDefined()) {
        std::string error = "[ERROR] [KeyError] 'name' sub-node is not defined.";
        std::string prompt = "Such node is required";
        throw std::runtime_error(error + " " + prompt);
    }
    if (!name_node.IsScalar()) {
        std::string error = "[ERROR] [NodeTypeError] 'name' sub-node is not a scalar-yaml-node.";
        std::string prompt = "Such a node is required to be a scalar-yaml-node.";
        throw std::runtime_error(error + " " + prompt);
    }
    std::string name = name_node.as<std::string>();
    std::vector<std::string> sub_namesapces = namesapces;
    sub_namesapces.push_back(name);
    // *************************************************************************   
    const YAML::Node enums_node = node["enums"];
    std::vector<std::shared_ptr < Enum>> enums;
    try {
        read_enums(enums_node, enums);
    } catch (const std::runtime_error& e) {
        const std::string where = "class " + name + " (in " + join(namesapces, "::") + ")";
        const std::string message = "[BACKTRACE] Error occurred when read inner enums for " + where + ".";
        throw std::runtime_error(message + "\n" + e.what());
    }
    // *************************************************************************    
    const YAML::Node classes_node = node["classes"];
    std::vector<std::shared_ptr < Class>> classes;
    try {
        read_classes(classes_node, sub_namesapces, classes);
    } catch (const std::runtime_error& e) {
        const std::string where = "class " + name + " (in " + join(namesapces, "::") + ")";
        const std::string message = "[BACKTRACE] Error occurred when read inner classes for " + where + ".";
        throw std::runtime_error(message + "\n" + e.what());
    }
    // *************************************************************************  
    const YAML::Node field_node = node["fields"];
    std::vector<std::shared_ptr < Field>> fields;
    try {
        read_fields(field_node, fields);
    } catch (const std::runtime_error& e) {
        const std::string where = "class " + name + " (in " + join(namesapces, "::") + ")";
        const std::string message = "[BACKTRACE] Error occurred when read fields for " + where + ".";
        throw std::runtime_error(message + "\n" + e.what());
    }
    // *************************************************************************  
    return std::make_shared<Class>(namesapces, name, enums, classes, fields);
}