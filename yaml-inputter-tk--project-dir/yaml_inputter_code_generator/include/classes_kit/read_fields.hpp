#ifndef CLASSES_KIT__READ_FIELDS_HPP
#define CLASSES_KIT__READ_FIELDS_HPP

#include<vector>
#include<memory>
#include<yaml-cpp/yaml.h>
#include<classes_kit/field.hpp>

void read_fields(
        const YAML::Node & node,
        std::vector<std::shared_ptr<Field>> &fields);

#endif