#include<iostream>
#include<iomanip>
#include<string>
#include"yaml-cpp/yaml.h"  // YAML::LoadFile

#include<input_data.hpp>
#include<input_data_fill_functions.hpp>

#define P(x) std::cout << std::setw(20) << std::left << #x << " : " << (x) << std::endl

int main(int argc, char** argv) {

    const std::string yaml_file_path = argv[1];

    YAML::Node root = YAML::LoadFile(yaml_file_path);
    yaml_inputter::Filler filler(root);
    InputData id;
    fill(id, filler);

    P(id.E);
    P(int(id.theory));    
    P(id.rs.size());
    for (size_t i = 0; i < id.rs.size(); i++) {
        P(i);
        P(id.rs[i].pA.x);
        P(id.rs[i].pA.y);
        P(id.rs[i].pB.x);
        P(id.rs[i].pB.y);
    }
    P(id.os.size());
    for (size_t i = 0; i < id.os.size(); i++) {
        P(i);
        P(id.os[i].pA.x);
        P(id.os[i].pA.y);
        P(id.os[i].pB.x);
        P(id.os[i].pB.y);
    }
    P(id.fi.size());
    for (size_t i = 0; i < id.fi.size(); i++) {
        P(id.fi[i]);
    }
    return 0;
}