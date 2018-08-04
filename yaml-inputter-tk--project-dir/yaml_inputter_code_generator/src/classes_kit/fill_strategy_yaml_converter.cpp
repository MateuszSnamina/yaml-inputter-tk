#include<string>
#include<sstream>
#include<classes_kit/fill_strategy_yaml_converter.hpp>

namespace YAML {

    // template<> not used for a member of a specialization
    Node convert<FillStrategy>::encode(const FillStrategy& rhs) {
        std::ostringstream oss;
        oss << rhs;
        std::string s = oss.str();
        YAML::Node node(s);
        return node;
    }

    // template<> not used for a member of a specialization
    bool convert<FillStrategy>::decode(const Node& node, FillStrategy& rhs) {
        if (!node.IsScalar())
            return false;
        std::string s = node.as<std::string>();
        std::istringstream iss(s);
        iss >> rhs;
        if (!iss) return false;
        return true;
    }

} // end of namespace YAML