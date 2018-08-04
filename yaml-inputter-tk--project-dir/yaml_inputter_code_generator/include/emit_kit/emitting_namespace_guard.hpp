#ifndef EMIT_KIT__EMITTING_NAMESPACE_GUARD
#define EMIT_KIT__EMITTING_NAMESPACE_GUARD

#include<string>
#include<writer_kit/writer.hpp>

class NamespaceGuard {
public:
    NamespaceGuard(Writer& writer, const std::string & namespace_name);
    ~NamespaceGuard();
private:
    Writer &writer;
    std::string namespace_name;
};
    

#endif