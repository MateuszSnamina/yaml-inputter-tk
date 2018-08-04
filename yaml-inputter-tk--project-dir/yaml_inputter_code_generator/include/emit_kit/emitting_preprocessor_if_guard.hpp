#ifndef EMIT_KIT__EMITTING_PREPROCESSOR_IF_GUARD_HPP
#define EMIT_KIT__EMITTING_PREPROCESSOR_IF_GUARD_HPP

#include<iostream>
#include<string>

class PreprocessorIfGuard {
public:
    PreprocessorIfGuard(std::ostream &s, const std::string & macro);
    ~PreprocessorIfGuard();
private:
    std::ostream &s;
    std::string macro;
};

#endif