#include<classes_kit/enum.hpp>
#include<ansi_escape_code.hpp>
#include<join.hpp>
#include<writer_kit/writer.hpp>

Enum::Enum(
        const std::string& cpp_name,
        const std::vector<std::string>& cpp_values) :
cpp_name(cpp_name),
cpp_values(cpp_values) {
}

std::string Enum::leaflet() const {
    std::string str = utility::BgColorGray + "enum " + cpp_name + utility::Reset;
    str += " {";
    str += join(cpp_values, " ");
    str += " }";
    return str;
}

std::vector<std::string> Enum::definition() const {
    std::vector<std::string> result;
    VectorWriter writer(result);
    writer.write_line("enum " + cpp_name + " {");
    writer.push_back_indent();
    for (std::size_t i = 0; i < cpp_values.size(); ++i) {
        const std::string ending = (i == cpp_values.size() - 1 ? "" : ",");
        writer.write_line(cpp_values[i] + ending);
    }
    writer.pop_indent();
    writer.write_line("};");
    return result;
}