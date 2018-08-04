#include<emit_kit/writer_leaflet.hpp>
#include<ansi_escape_code.hpp>
#include<join.hpp>

WriterLeafletIn::WriterLeafletIn(Writer & writer) :
writer(writer) {
}

void WriterLeafletIn::operator()(const Class& c) const {
    std::string str = utility::BgColorRed + "struct " + utility::Bold + c.name + utility::Reset;
    writer.write_line(str);
    writer.push_back_indent("  | ");
    for (const auto & e : c.inner_enums)
        writer.write_line(e->leaflet());    
}

WriterLeafletOut::WriterLeafletOut(Writer & writer) :
writer(writer) {
}

void WriterLeafletOut::operator()(const Class& c) const {
    for (const auto & field : c.fields)
        writer.write_line(field->leaflet());    
    writer.pop_indent();
}
