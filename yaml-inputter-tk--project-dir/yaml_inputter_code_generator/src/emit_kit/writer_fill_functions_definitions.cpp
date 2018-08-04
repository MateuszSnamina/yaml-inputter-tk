#include<vector>

#include<emit_kit/writer_fill_functions_definitions.hpp>
#include<join.hpp>

WriterFillFunctionsDefinitionsIn::WriterFillFunctionsDefinitionsIn(Writer & writer) :
writer(writer) {
}

void WriterFillFunctionsDefinitionsIn::operator()(const Class& c) const {
}

WriterFillFunctionsDefinitionsOut::WriterFillFunctionsDefinitionsOut(Writer & writer) :
writer(writer) {
}

void WriterFillFunctionsDefinitionsOut::operator()(const Class& c) const {
    writer.write_line("template<class... Ts>");
    std::vector<std::string> all_names = c.namesapces;
    all_names.push_back(c.name);
    const std::string full_class_name = join(all_names, "::");
    std::string syg = "void";
    syg += " ";
    syg += "fill";
    syg += "(";
    syg += full_class_name + "& instance,";
    syg += " " "const yaml_inputter::Filler & filler,";
    syg += " " "Ts&&... keys";
    syg += ")";
    writer.write_line(syg + " {");
    writer.push_back_indent();
    for (const auto & field : c.fields)
        writer.write_lines(field->fill());
    std::vector<std::string> correct_fields;
    for (const auto & field : c.fields)
        if (auto field_with_key = std::dynamic_pointer_cast<FieldWithKeys>(field)) {
            correct_fields.push_back(field_with_key->input_keys[0]);
        }
    if (!correct_fields.empty()) {
        writer.write_line("{  // check-stray-fields block");
        writer.push_back_indent();
        writer.write_line("std::set<std::string> correct_fields = {" + join(correct_fields, ", ") + "};");
        writer.write_line("filler.check_stray_fields(correct_fields, std::forward<Ts>(keys)...);");
        writer.pop_indent();
        writer.write_line("} // end of check-stray-fields block");
    }
    writer.pop_indent();
    writer.write_line("} // end of fill function");
    writer.write_line("");
}
