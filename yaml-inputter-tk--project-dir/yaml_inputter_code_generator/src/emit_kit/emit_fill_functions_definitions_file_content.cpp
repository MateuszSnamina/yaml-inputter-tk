#include<emit_kit/emit_fill_functions_definitions_file_content.hpp>
#include<classes_kit/classes_dfs.hpp>
#include<emit_kit/writer_fill_functions_definitions.hpp>
#include<emit_kit/emit_overriding_warning.hpp>
#include<emit_kit/emitting_preprocessor_if_guard.hpp>
#include<emit_kit/emitting_namespace_guard.hpp>

namespace {

    void __emit_fill_functions_definitions_file_content(
            Writer& writer,
            const std::vector<std::shared_ptr<Class>>&classes) {
        WriterFillFunctionsDefinitionsIn writer_in(writer);
        WriterFillFunctionsDefinitionsOut writer_out(writer);
        ClassesDfs dfs(writer_in, writer_out);
        for (std::shared_ptr<Class> c : classes)
            dfs.go(*c);
    }

    void _emit_fill_functions_definitions_file_content(
            Writer& writer,
            const std::vector<std::string>::const_iterator classes_namespace_begin,
            const std::vector<std::string>::const_iterator classes_namespace_end,
            const std::vector<std::shared_ptr<Class>>&classes) {
        if (classes_namespace_begin != classes_namespace_end) {
            auto guard = NamespaceGuard(writer, *classes_namespace_begin);
            _emit_fill_functions_definitions_file_content(writer, classes_namespace_begin + 1, classes_namespace_end, classes);
        } else
            __emit_fill_functions_definitions_file_content(writer, classes);
    }

} // end of anomyous namespace

void emit_fill_functions_definitions_file_content(
        std::ostream& s,
        const std::vector<std::string>& headers_to_include,
        const std::vector<std::string>& classes_namespace,
        const std::vector<std::shared_ptr<Class>>&classes) {
    emit_overriding_warning(s);
    const std::string heager_guard_macro = "INPUT_DATA_FILL_FUNCTIONS_HPP";
    PreprocessorIfGuard pig(s, heager_guard_macro);
    s << "#include<set> // set used in check-stray-fields block" << std::endl;
    s << "#include<yaml_inputter/templated_filler.hpp>" << std::endl;
    for (const std::string& header : headers_to_include)
        s << "#include" + header + " // user request header" << std::endl;
    s << std::endl;
    StreamWriter writer(s);
    _emit_fill_functions_definitions_file_content(
            writer,
            classes_namespace.cbegin(), classes_namespace.cend(),
            classes);
}
