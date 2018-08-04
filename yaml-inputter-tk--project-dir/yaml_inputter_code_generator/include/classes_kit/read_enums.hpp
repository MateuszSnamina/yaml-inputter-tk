#ifndef CLASSES_KIT__READ_ENUMS_HPP
#define CLASSES_KIT__READ_ENUMS_HPP

#include<vector>
#include<memory>
#include<yaml-cpp/yaml.h>
#include<classes_kit/enum.hpp>

void read_enums(
        const YAML::Node & node,
        std::vector<std::shared_ptr<Enum>> &enums);

#endif