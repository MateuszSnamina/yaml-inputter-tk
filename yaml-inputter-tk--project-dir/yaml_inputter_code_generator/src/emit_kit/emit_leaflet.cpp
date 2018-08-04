#include<emit_kit/emit_leaflet.hpp>
#include<classes_kit/classes_dfs.hpp>
#include<emit_kit/writer_leaflet.hpp>

void emit_leaflet(
        std::ostream& s,
        const std::vector<std::shared_ptr<Class>>&classes) {
    StreamWriter writer(s);
    WriterLeafletIn writer_in(writer);
    WriterLeafletOut writer_out(writer);
    ClassesDfs dfs(writer_in, writer_out);
    for (std::shared_ptr<Class> c : classes)
        dfs.go(*c);
}