cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wpedantic -pthread")

# Main parts:
add_subdirectory(yaml_inputter)
add_subdirectory(yaml_inputter_code_generator)
# Exemplary program:
add_subdirectory(filler_api_example1)
add_subdirectory(filler_api_example2)
add_subdirectory(tk_example)
