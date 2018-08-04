cmake_minimum_required(VERSION 2.8)

file(GLOB cpp_files src/*.cpp)
file(GLOB hpp_files include/*.hpp)

add_executable(filler_api_example1 ${cpp_files})
target_include_directories(filler_api_example1 PUBLIC include)
target_include_directories(filler_api_example1 PUBLIC ../yaml_inputter/include)
target_link_libraries(filler_api_example1 yaml-cpp)

#target_include_directories(yaml_inputter_tester PUBLIC ../yaml_inputter/include)

