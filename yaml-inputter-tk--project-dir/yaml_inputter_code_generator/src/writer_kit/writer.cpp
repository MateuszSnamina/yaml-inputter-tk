#include<writer_kit/writer.hpp>

// *****************************************************************************
// **************  Abstract base class            ******************************
// *****************************************************************************

void Writer::write_lines(const std::vector<std::string> & strs) const {
    for (const std::string & str : strs)
        write_line(str);
}

std::string Writer::concatenate_indents() const {
    std::string result;
    for (const auto & indent : indents)
        result += indent;
    return result;
}

void Writer::push_back_indent(const std::string& indent) {
    indents.push_back(indent);
}

void Writer::pop_indent() {
    indents.pop_back();
}

// *****************************************************************************
// **************  Concrete subclasses            ******************************
// *****************************************************************************

StreamWriter::StreamWriter(std::ostream & os) :
os(os) {
}

void StreamWriter::write_line(const std::string & str) const {
    os << concatenate_indents() << str << std::endl;
}

// *****************************************************************************

VectorWriter::VectorWriter(std::vector<std::string>& result) :
result(result) {
}

void VectorWriter::write_line(const std::string & str) const {
    result.push_back(concatenate_indents() + str);
}


