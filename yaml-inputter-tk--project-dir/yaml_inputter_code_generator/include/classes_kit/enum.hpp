#ifndef CLASSES_KIT__ENUM_HPP
#define CLASSES_KIT__ENUM_HPP

#include<string>
#include<vector>

class Enum {
public:
    Enum(
            const std::string& cpp_name,
            const std::vector<std::string>& cpp_values);
    std::string leaflet() const;
    std::vector<std::string> definition() const;
public:
    const std::string cpp_name;
    const std::vector<std::string> cpp_values;
};


#endif
