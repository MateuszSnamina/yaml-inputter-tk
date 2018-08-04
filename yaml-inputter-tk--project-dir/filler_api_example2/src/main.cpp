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
    std::vector<LineSegment> s;	// The novelty.
};

int main(int argc, char** argv) {

    const std::string yaml_file_path = argv[1];
    const YAML::Node root = YAML::LoadFile(yaml_file_path);
    const yaml_inputter::Filler filler(root);

    InpudData id;
    filler.target(id.method).fill_required_scalar("method");
    filler.target(id.energy).fill_required_scalar("energy");

    size_t sequence_size = filler.required_sequence_size("segments");
    id.s.resize(sequence_size);
    for (size_t i = 0; i < sequence_size; i++) {
        filler.target(id.s[i].pA.x).fill_required_scalar("segments", i, "pA", "x");
        filler.target(id.s[i].pA.y).fill_required_scalar("segments", i, "pA", "y");
        filler.target(id.s[i].pB.x).fill_required_scalar("segments", i, "pB", "x");
        filler.target(id.s[i].pB.y).fill_required_scalar("segments", i, "pB", "y");
    }

    P(id.method);
    P(id.energy);
    P(id.s.size());
    for (size_t i = 0; i < id.s.size(); i++) {
        P(id.s[i].pA.x);
        P(id.s[i].pA.y);
        P(id.s[i].pB.x);
        P(id.s[i].pB.y);
    }

    return 0;
}
