#include<emit_kit/emit_overriding_warning.hpp>

#include<chrono>
#include<ctime>

void emit_overriding_warning(std::ostream& s) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    s << "/* Header file generated automatically by yaml-inputter-tk-code-generator." << std::endl;
    s << " * The header content is based on the provided input-data-specification file." << std::endl;
    s << " * File generation date: " << std::ctime(&in_time_t) << std::flush;
    s << " * WARNING: Do not modify this file!" << std::endl;
    s << " * (Every change will be overridden during the next compilation.)" << std::endl;
    s << " */" << std::endl;
    s << std::endl;
}