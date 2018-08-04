cmake_minimum_required(VERSION 2.8)

file(GLOB cpp_files src/*.cpp src/classes_kit/*.cpp src/writer_kit/*.cpp src/emit_kit/*.cpp)

add_executable(yaml_inputter_code_generator ${cpp_files})
target_include_directories(yaml_inputter_code_generator PUBLIC include)
target_link_libraries(yaml_inputter_code_generator yaml-cpp)
target_link_libraries(yaml_inputter_code_generator boost_program_options)
