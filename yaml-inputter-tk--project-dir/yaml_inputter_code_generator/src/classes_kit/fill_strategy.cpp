#include<sstream>
#include<classes_kit/fill_strategy.hpp>

std::ostream& operator<<(std::ostream& os, const FillStrategy& o) {
    switch (o) {
        case FillStrategy::None:
            os << "none";
            return os;
        case FillStrategy::Required:
            os << "required";
            return os;
        case FillStrategy::RequiredScalar:
            os << "required-scalar";
            return os;
        case FillStrategy::Optional:
            os << "optional";
            return os;
        case FillStrategy::OptionalScalar:
            os << "optional-scalar";
            return os;
        case FillStrategy::Delegated:
            os << "delegated";
            return os;
        default: exit(51);            
    }
}

std::istream& operator>>(std::istream& is, FillStrategy& o) {
    std::string str;
    is >> str;
    if (str == "none") {
        o = FillStrategy::None;
        return is;
    }
    if (str == "required") {
        o = FillStrategy::Required;
        return is;
    }
    if (str == "required-scalar") {
        o = FillStrategy::RequiredScalar;
        return is;
    }
    if (str == "optional") {
        o = FillStrategy::Optional;
        return is;
    }
    if (str == "optional-scalar") {
        o = FillStrategy::OptionalScalar;
        return is;
    }
    if (str == "delegated") {
        o = FillStrategy::Delegated;
        return is;
    }
    is.setstate(std::ios::failbit);
    return is;

}

std::string to_string(FillStrategy o) {
    std::ostringstream oss;
    oss << o;
    return oss.str();
}