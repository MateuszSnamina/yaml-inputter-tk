#ifndef CLASSES_KIT__FILL_STRATEGY_HPP
#define CLASSES_KIT__FILL_STRATEGY_HPP

#include<iostream>
#include<string>

enum class FillStrategy {
    None,
    Required,
    RequiredScalar,    
    Optional,
    OptionalScalar,    
    Delegated
};

std::ostream& operator<<(std::ostream& os, const FillStrategy& o);
std::istream& operator>>(std::istream& is, FillStrategy& o);

std::string to_string(FillStrategy);
#endif