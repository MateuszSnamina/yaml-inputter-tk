#ifndef CLASSES_KIT__CLASS_HPP
#define CLASSES_KIT__CLASS_HPP

#include<string>
#include<vector>
#include<memory>
#include<classes_kit/field.hpp>
#include<classes_kit/enum.hpp>

struct Class {
    Class(
            const std::vector<std::string>& namesapces,
            const std::string& name,
            const std::vector<std::shared_ptr<Enum>>&inner_enums,
            const std::vector<std::shared_ptr<Class>>&inner_classes,
            const std::vector<std::shared_ptr<Field>>&fields);
    std::vector<std::string> namesapces;
    std::string name;
    std::vector<std::shared_ptr<Enum>> inner_enums;
    std::vector<std::shared_ptr<Class>> inner_classes;
    std::vector<std::shared_ptr<Field>> fields;
};

inline Class::Class(
        const std::vector<std::string>& namesapces,
        const std::string& name,
        const std::vector<std::shared_ptr<Enum>>&inner_enums,
        const std::vector<std::shared_ptr<Class>>&inner_classes,
        const std::vector<std::shared_ptr<Field>>&fields) :
namesapces(namesapces),
name(name),
inner_enums(inner_enums),
inner_classes(inner_classes),
fields(fields) {
}

#endif