#ifndef CLASSES_KIT__CHECK_STRAY_FIELDS_HPP
#define CLASSES_KIT__CHECK_STRAY_FIELDS_HPP

#include<yaml-cpp/yaml.h>

void check_stray_fields(const std::set<std::string>& valid_fields, const YAML::Node& node);

#endif
