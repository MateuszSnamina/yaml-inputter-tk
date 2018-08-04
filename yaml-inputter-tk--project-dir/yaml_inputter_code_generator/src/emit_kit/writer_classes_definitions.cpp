#include<emit_kit/writer_classes_definitions.hpp>
#include<join.hpp>

WriterClassesDefinitionsIn::WriterClassesDefinitionsIn(Writer & writer) :
writer(writer) {
}

void WriterClassesDefinitionsIn::operator()(const Class& c) const {
    std::string str = "struct " + c.name + " {";
    writer.write_line(str);
    writer.push_back_indent("    ");
    for (const auto & e : c.inner_enums)
        writer.write_lines(e->definition());    
}

WriterClassesDefinitionsOut::WriterClassesDefinitionsOut(Writer & writer) :
writer(writer) {
}

void WriterClassesDefinitionsOut::operator()(const Class& c) const {
    for (const auto & field : c.fields)
        writer.write_line(field->definition());
    writer.pop_indent();
    writer.write_line("};");
}

