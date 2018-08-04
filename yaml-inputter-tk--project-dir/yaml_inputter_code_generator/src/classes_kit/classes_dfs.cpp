#include<classes_kit/classes_dfs.hpp>

ClassesDfs::ClassesDfs(
        std::function<void(const Class&) > in,
        std::function<void(const Class&) > out) :
in(in),
out(out) {
}

void ClassesDfs::go(const Class& c) const {
    in(c);
    for (const std::shared_ptr<Class> & ic : c.inner_classes)
        go(*ic);
    out(c);
}

