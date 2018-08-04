#ifndef CLASSES_KIT__READ_CLASSES_HPP
#define CLASSES_KIT__READ_CLASSES_HPP

#include<string>
#include<vector>
#include<yaml-cpp/yaml.h>
#include<classes_kit/class.hpp>

void read_classes(
        const YAML::Node & node,
        const std::vector<std::string> & namesapces,
        std::vector<std::shared_ptr<Class>> & classes);

#endif