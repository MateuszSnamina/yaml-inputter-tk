cmake_minimum_required(VERSION 2.8)

file(GLOB cpp_files src/*.cpp)
file(GLOB hpp_files include/*.hpp)

add_executable(tk_example ${cpp_files})
target_include_directories(tk_example PUBLIC include)
target_include_directories(tk_example PUBLIC ../yaml_inputter/include)
target_link_libraries(tk_example yaml-cpp)

#target_include_directories(yaml_inputter_tester PUBLIC ../yaml_inputter/include)

