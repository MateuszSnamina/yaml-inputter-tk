#ifndef EMIT_KIT__WRITER_HEADER_HPP
#define EMIT_KIT__WRITER_HEADER_HPP

#include<classes_kit/class.hpp>
#include<writer_kit/writer.hpp>

class WriterClassesDefinitionsIn {
private:
    Writer & writer;
public:
    WriterClassesDefinitionsIn(Writer & writer);
    void operator()(const Class& c) const;
};

class WriterClassesDefinitionsOut {
private:
    Writer & writer;
public:
    WriterClassesDefinitionsOut(Writer & writer);
    void operator()(const Class& c) const;
};

#endif