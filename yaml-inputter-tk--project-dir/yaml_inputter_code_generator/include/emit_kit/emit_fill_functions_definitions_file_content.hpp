#ifndef EMIT_KIT__EMIT_FILL_FUNCTIONS_DEFINITIONS_FILE_CONTENT_HPP
#define EMIT_KIT__EMIT_FILL_FUNCTIONS_DEFINITIONS_FILE_CONTENT_HPP

#include<ostream>
#include<classes_kit/class.hpp>


void emit_fill_functions_definitions_file_content(
        std::ostream& s,
        const std::vector<std::string>& headers_to_include,
        const std::vector<std::string>& classes_namespace,
        const std::vector<std::shared_ptr<Class>>& classes);

#endif