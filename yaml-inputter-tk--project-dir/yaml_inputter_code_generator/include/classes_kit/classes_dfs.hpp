#ifndef CLASSES_KIT__CLASSES_DFS_HPP
#define CLASSES_KIT__CLASSES_DFS_HPP

#include<functional>
#include<classes_kit/class.hpp>

class ClassesDfs {
private:
    std::function<void(const Class&) > in;
    std::function<void(const Class&) > out;
public:
    ClassesDfs(
            std::function<void(const Class&) > in,
            std::function<void(const Class&) > out);
    void go(const Class&) const;
};

#endif