#include<classes_kit/check_stray_fields.hpp>

void check_stray_fields(const std::set<std::string>& valid_fields, const YAML::Node& node) {
    if (!node.IsMap()) {
        const std::string message = "[ERROR] Error while checking stray fields - the checked node is not a map.";
        throw std::runtime_error(message);
    }
    for (auto it = node.begin(); it != node.end(); ++it) {
        const YAML::Node key = it->first;
        //const YAML::Node value = it->second;
        const std::string key_string = key.as<std::string>();
        if (!valid_fields.count(key_string)) {
            const std::string message = "[ERROR] Stray field '" + key_string + "' found.";
            throw std::runtime_error(message);
        }
    }
}