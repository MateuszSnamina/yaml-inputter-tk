#ifndef CLASSES_KIT__MAKE_FIELD_HPP
#define CLASSES_KIT__MAKE_FIELD_HPP

#include<yaml-cpp/yaml.h>
#include<classes_kit/field.hpp>
#include<memory>

std::shared_ptr<Field> make_field(const YAML::Node & node);

#endif 