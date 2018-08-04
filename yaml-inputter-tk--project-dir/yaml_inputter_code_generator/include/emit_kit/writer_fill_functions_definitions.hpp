#ifndef EMIT_KIT__LEAFLET_BUILD_FUNCTIONS_HPP
#define EMIT_KIT__LEAFLET_BUILD_FUNCTIONS_HPP

#include<classes_kit/class.hpp>
#include<writer_kit/writer.hpp>

class WriterFillFunctionsDefinitionsIn {
private:
    Writer & writer;
public:
    WriterFillFunctionsDefinitionsIn(Writer & writer);
    void operator()(const Class& c) const;
};

class WriterFillFunctionsDefinitionsOut {
private:
    Writer & writer;
public:
    WriterFillFunctionsDefinitionsOut(Writer & writer);
    void operator()(const Class& c) const;
};

#endif