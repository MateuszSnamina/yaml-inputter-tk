#include<emit_kit/emitting_namespace_guard.hpp>

NamespaceGuard::NamespaceGuard(Writer& writer, const std::string & namespace_name) :
writer(writer), namespace_name(namespace_name) {
    writer.write_line("namespace " + namespace_name + " {");
    writer.push_back_indent();
}

NamespaceGuard::~NamespaceGuard() {
    writer.pop_indent();
    writer.write_line("} // end of namespace " + namespace_name);
}
