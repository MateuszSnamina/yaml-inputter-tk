#ifndef CLASSES_KIT__CONTAINER_TYPE_HPP
#define CLASSES_KIT__CONTAINER_TYPE_HPP

#include<iostream>
#include<string>

enum class ContainerType {
    None,
    RequiredSequence,
    OptionalSequence,
    FixedSizeSequence
};

std::ostream& operator<<(std::ostream& os, const ContainerType& o);
std::istream& operator>>(std::istream& is, ContainerType& o);

std::string to_string(ContainerType);
#endif