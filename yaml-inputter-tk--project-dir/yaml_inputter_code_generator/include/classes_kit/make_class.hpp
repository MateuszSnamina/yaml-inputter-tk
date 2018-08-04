#ifndef CLASSES_KIT__MAKE_CLASS_HPP
#define CLASSES_KIT__MAKE_CLASS_HPP

#include<string>
#include<vector>
#include<yaml-cpp/yaml.h>
#include<classes_kit/class.hpp>

std::shared_ptr<Class> make_class(const YAML::Node & node,
        const std::vector<std::string> & namesapces);

#endif 