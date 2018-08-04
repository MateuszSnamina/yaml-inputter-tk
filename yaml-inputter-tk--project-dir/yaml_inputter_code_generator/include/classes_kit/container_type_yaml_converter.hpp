#ifndef CLASSES_KIT__CONTAINER_TYPE_YAML_CONVERTER_HPP
#define CLASSES_KIT__CONTAINER_TYPE_YAML_CONVERTER_HPP

#include<yaml-cpp/yaml.h>
#include<classes_kit/container_type.hpp>

namespace YAML {

    template<>
    struct convert<ContainerType> {
        static Node encode(const ContainerType& rhs);
        static bool decode(const Node& node, ContainerType& rhs);
    };

} // end of namespace YAML

#endif