#ifndef EMIT_KIT__LEAFLET_HEADER_HPP
#define EMIT_KIT__LEAFLET_HEADER_HPP

#include<classes_kit/class.hpp>
#include<writer_kit/writer.hpp>

class WriterLeafletIn {
private:
    Writer & writer;
public:
    WriterLeafletIn(Writer & writer);
    void operator()(const Class& c) const;
};

class WriterLeafletOut {
private:
    Writer & writer;
public:
    WriterLeafletOut(Writer & writer);
    void operator()(const Class& c) const;
};

#endif