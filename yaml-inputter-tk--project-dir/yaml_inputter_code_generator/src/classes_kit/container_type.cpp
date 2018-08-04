#include<sstream>
#include<classes_kit/container_type.hpp>

std::ostream& operator<<(std::ostream& os, const ContainerType& o) {
    switch (o) {
        case ContainerType::None:
            os << "none";
            return os;
        case ContainerType::RequiredSequence:
            os << "required-sequence";
            return os;
        case ContainerType::OptionalSequence:
            os << "optional-sequence";
            return os;
        case ContainerType::FixedSizeSequence:
            os << "fixed-size-sequence";
            return os;            
        default: exit(50);
    }
}

std::istream& operator>>(std::istream& is, ContainerType& o) {
    std::string str;
    is >> str;
    if (str == "none") {
        o = ContainerType::None;
        return is;
    }
    if (str == "required-sequence") {
        o = ContainerType::RequiredSequence;
        return is;
    }
    if (str == "optional-sequence") {
        o = ContainerType::OptionalSequence;
        return is;
    }
    if (str == "fixed-size-sequence") {
        o = ContainerType::FixedSizeSequence;
        return is;
    }
    is.setstate(std::ios::failbit);
    return is;

}

std::string to_string(ContainerType o) {
    std::ostringstream oss;
    oss << o;
    return oss.str();
}