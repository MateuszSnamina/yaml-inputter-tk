#include<iostream>
#include<iomanip>
#include<string>
#include<yaml-cpp/yaml.h>  // YAML::LoadFile
#include<yaml_inputter/templated_filler.hpp> // class yaml_inputter::Filler

#define P(x) std::cout << std::setw(20) << std::left << #x << " : " << (x) << std::endl

struct InpudData {

    struct LineSegment {

        struct Point {
            int x;
            int y;
        };
        Point pA;
        Point pB;
    };
    unsigned method;
    double energy;
    LineSegment s1;
    LineSegment s2;
};

int main(int argc, char** argv) {

    const std::string yaml_file_path = argv[1];
    const YAML::Node root = YAML::LoadFile(yaml_file_path);
    const yaml_inputter::Filler filler(root);

    InpudData id;
    filler.target(id.method).fill_required_scalar("method");
    filler.target(id.energy).fill_required_scalar("energy");
    filler.target(id.s1.pA.x).fill_required_scalar("segments", 0, "pA", "x");
    filler.target(id.s1.pA.y).fill_required_scalar("segments", 0, "pA", "y");
    filler.target(id.s1.pB.x).fill_required_scalar("segments", 0, "pB", "x");
    filler.target(id.s1.pB.y).fill_required_scalar("segments", 0, "pB", "y");
    filler.target(id.s2.pA.x).fill_required_scalar("segments", 1, "pA", "x");
    filler.target(id.s2.pA.y).fill_required_scalar("segments", 1, "pA", "y");
    filler.target(id.s2.pB.x).fill_required_scalar("segments", 1, "pB", "x");
    filler.target(id.s2.pB.y).fill_required_scalar("segments", 1, "pB", "y");

    P(id.method);
    P(id.energy);
    P(id.s1.pA.x);
    P(id.s1.pA.y);
    P(id.s1.pB.x);
    P(id.s1.pB.y);
    P(id.s2.pA.x);
    P(id.s2.pA.y);
    P(id.s2.pB.x);
    P(id.s2.pB.y);

    return 0;
}