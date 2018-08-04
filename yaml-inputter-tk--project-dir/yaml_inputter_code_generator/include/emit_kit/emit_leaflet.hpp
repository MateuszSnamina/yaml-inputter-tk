#ifndef EMIT_KIT__EMIT_LEAFLET_HPP
#define EMIT_KIT__EMIT_LEAFLET_HPP

#include<ostream>
#include<classes_kit/class.hpp>

void emit_leaflet(
        std::ostream& s,
        const std::vector<std::shared_ptr<Class>>& classes);

#endif