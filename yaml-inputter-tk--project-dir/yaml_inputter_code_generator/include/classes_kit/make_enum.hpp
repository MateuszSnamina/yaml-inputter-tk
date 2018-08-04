#ifndef CLASSES_KIT__MAKE_ENUM_HPP
#define CLASSES_KIT__MAKE_ENUM_HPP

#include<yaml-cpp/yaml.h>
#include<classes_kit/enum.hpp>
#include<memory>

std::shared_ptr<Enum> make_enum(const YAML::Node & node);


#endif
