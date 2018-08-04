#include<emit_kit/emitting_preprocessor_if_guard.hpp>

PreprocessorIfGuard::PreprocessorIfGuard(std::ostream &s, const std::string & macro) :
s(s), macro(macro) {
    s << "#ifndef " << macro << std::endl;
    s << "#define " << macro << std::endl;
    s << " " << std::endl;
}

PreprocessorIfGuard::~PreprocessorIfGuard() {
    s << "#endif // end of #ifndef " << macro << std::endl;
}