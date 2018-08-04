#ifndef INPUT_DATA_YAML_CONVERSIONS_HPP
#define INPUT_DATA_YAML_CONVERSIONS_HPP

#include<string>
#include<yaml-cpp/yaml.h>
#include<input_data.hpp>
#include<length.hpp>

namespace YAML {

    template<>
    struct convert<InputData::Theory> {
        static bool decode(const Node& n, InputData::Theory& v);
    };

    template<>
    struct convert<Length> {
        static bool decode(const Node& n, Length& l);
    };

    inline bool convert<InputData::Theory>::decode(const Node& n, InputData::Theory& v) {
        if (!n.IsScalar()) return false;
        const std::string s = n.as<std::string>();
        if (s == "single_point") v = InputData::SINGLE_POINT;
        else if (s == "optimization") v = InputData::OPTIMIZATION;
        else return false;
        return true;
    }

    inline bool convert<Length>::decode(const Node& n, Length& l) {
        if (!n.IsScalar()) return false;
        try {
            const std::string s = n.as<std::string>();
            std::size_t pos;
            const double v = std::stod(s, &pos);
            const std::string suffix(s, pos);
            if (suffix == "")
                l = Length::from_au(v);
            else if (suffix == "A" || suffix == "Angst")
                l = Length::from_angstrom(v);
            else return false;
            return true;
        } catch (...) {
            return false;
        }
    }

} // end of namespace YAML

#endif