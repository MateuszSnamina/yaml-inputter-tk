#ifndef CLASSES_KIT__FILL_STRATEGY_YAML_CONVERTER_HPP
#define CLASSES_KIT__FILL_STRATEGY_YAML_CONVERTER_HPP

#include<yaml-cpp/yaml.h>
#include<classes_kit/fill_strategy.hpp>

namespace YAML {

    template<>
    struct convert<FillStrategy> {
        static Node encode(const FillStrategy& rhs);
        static bool decode(const Node& node, FillStrategy& rhs);
    };

} // end of namespace YAML

#endif