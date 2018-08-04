#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<memory>
#include<yaml-cpp/yaml.h>
#include<boost/program_options.hpp>

#include<classes_kit/class.hpp>
#include<classes_kit/read_classes.hpp>

#include<emit_kit/emit_classes_definitions_file_content.hpp>
#include<emit_kit/emit_fill_functions_definitions_file_content.hpp>
#include<emit_kit/emit_leaflet.hpp>


// *****************************************************************************

namespace po = boost::program_options;

void emit_help(std::ostream& s, const po::options_description & desc) {
    s << "Program name: yaml-inputter-code-generator" << std::endl;
    s << std::endl;
    s << desc << std::endl;
    s << "Positional arguments:" << std::endl;
    s << "First positional argument will be treated as class-spec-path." << std::endl;
    s << "Second positional argument will be treated as includes-spec-path." << std::endl;
}

int main(int argc, char** argv) {

    std::string class_specification_file_path;
    std::string classes_definitions_file_path;
    std::string fill_functions_definitions_file_path;
    std::vector<std::string> classes_namespace;    
    std::vector<std::string> classes_definitions_include;
    std::vector<std::string> fill_functions_definitions_include;

    po::options_description desc("Allowed named arguments:");
    desc.add_options()
            // --help:
            ("help,h",
            "produce help message")

            // --class-spec-path, -s:
            ("class-spec-path,s",
            po::value<std::string>(&class_specification_file_path)
            ->required(),
            "file path of input-data-specification to process.")

            // --namespace, -n:
            ("namespace,n",
            po::value<std::vector < std::string >> (&classes_namespace)->multitoken(),
            "namespace of the input-data classes.")
            
            // --classes-include-list, -i:
            ("classes-include-list,i",
            po::value<std::vector < std::string >> (&classes_definitions_include)->multitoken(),
            "list of the headers to include on top of the header file containing input-data class definition.")
            
            // --class-def-path, -c:
            ("classes-def-path,c",
            po::value<std::string>(&classes_definitions_file_path)
            ->default_value("input_data.hpp"),
            "file path for generated header file containing input-data class definition.")

            // --functions-include-list, -j:
            ("functions-include-list,j",
            po::value<std::vector < std::string >> (&fill_functions_definitions_include)->multitoken(),
            "list of the headers to include on top of the header file containing functions fill(...) definitions.")
            
            // --functions-def-path, -f:
            ("functions-def-path,f",
            po::value<std::string>(&fill_functions_definitions_file_path)
            ->default_value("input_data_fill_functions.hpp"),
            "file path for generated header file containing functions fill(...) definitions.")
            ;
    
    po::positional_options_description p;
    p.add("class-spec-path", 1);

    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm); // may throw
        if (vm.count("help")) {
            emit_help(std::cout, desc);
            return 1;
        }
        // sets auto variables (eq. class_specification_file_path),
        // throw is required variable is missing:
        po::notify(vm); // may throw
    } catch (po::error& e) {
        std::cerr << "[GLOBAL ERROR] [PROGRAM OPTIONS ERROR]: " << e.what() << std::endl;
        std::cerr << std::endl;
        emit_help(std::cerr, desc);
        return 1;
    }

    std::cout << "[INFO] [PROGRAM OPTION] "
            << std::setw(40) << std::left
            << "class_specification_file_path" << " : "
            << class_specification_file_path;
    std::cout << std::endl;

    std::cout << "[INFO] [PROGRAM OPTION] "
            << std::setw(40) << std::left
            << "classes_namespace" << " : ";
    for (const std::string& s : classes_namespace)
        std::cout << s << " ";
    std::cout << std::endl;

    std::cout << "[INFO] [PROGRAM OPTION] "
            << std::setw(40) << std::left
            << "classes_definitions_include" << " : ";
    for (const std::string& s : classes_definitions_include)
        std::cout << s << " ";
    std::cout << std::endl;

    std::cout << "[INFO] [PROGRAM OPTION] "
            << std::setw(40) << std::left
            << "classes_definitions_file_path" << " : "
            << classes_definitions_file_path;
    std::cout << std::endl;

    std::cout << "[INFO] [PROGRAM OPTION] "
            << std::setw(40) << std::left
            << "fill_functions_definitions_include" << " : ";
    for (const std::string& s : fill_functions_definitions_include)
        std::cout << s << " ";
    std::cout << std::endl;
    
    std::cout << "[INFO] [PROGRAM OPTION] "
            << std::setw(40) << std::left
            << "fill_functions_definitions_file_path" << " : "
            << fill_functions_definitions_file_path;
    std::cout << std::endl;
    
    // *************************************************************************
    std::cout << "[INFO] Program is about to load class-specification-file." << std::endl;
    YAML::Node input_data_specification_node;
    try {
        input_data_specification_node = YAML::LoadFile(class_specification_file_path);
    } catch (const YAML::BadFile& e) {
        std::cerr << "[GLOBAL ERROR] when loading the class-specification-file" << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
    std::cout << "[INFO] Class-specification-file was loaded successfully." << std::endl;

    // *************************************************************************
    std::cout << "[INFO] Program is about to parse input-data-classes specification." << std::endl;
    std::vector<std::string> namesapces;
    std::vector<std::shared_ptr < Class>> classes;
    try {
        read_classes(input_data_specification_node, namesapces, classes);
    } catch (const std::runtime_error& e) {
        std::cerr << "[GLOBAL ERROR] when parse input-data-specification file." << std::endl;
        std::cerr << e.what() << std::endl;
        std::cerr << std::endl;
        return 1;
    }
    std::cout << "[INFO] parsed input-data-classes specification successfully." << std::endl;

    // *************************************************************************    
    std::cout << "[INFO] Program is about to emit leaflet." << std::endl;
    emit_leaflet(std::cout, classes);
    std::cout << "[INFO] Program emitted leaflet successfully." << std::endl;

    // *************************************************************************
    std::cout << "[INFO] Program is about to emit classes-definitions-file." << std::endl;
    std::ofstream classes_definitions_file(classes_definitions_file_path);
    if (!classes_definitions_file) {
        std::cerr << "[GLOBAL ERROR] problem with opening classes-definitions-file." << std::endl;
        return 10;
    }
    emit_classes_definitions_file_content(classes_definitions_file, classes_definitions_include, classes_namespace, classes);
    std::cout << "[INFO] Program emitted classes-definitions-file successfully." << std::endl;

    // *************************************************************************
    std::cout << "[INFO] Program is about to emit fill-functions-definitions-file." << std::endl;
    std::ofstream fill_functions_definitions_file(fill_functions_definitions_file_path);
    if (!fill_functions_definitions_file) {
        std::cerr << "[GLOBAL ERROR] problem with opening fill-functions-definitions-file." << std::endl;
        return 11;
    }
    emit_fill_functions_definitions_file_content(fill_functions_definitions_file, fill_functions_definitions_include, classes_namespace, classes);
    std::cout << "[INFO] Program emitted fill-functions-definitions-file successfully." << std::endl;

}
