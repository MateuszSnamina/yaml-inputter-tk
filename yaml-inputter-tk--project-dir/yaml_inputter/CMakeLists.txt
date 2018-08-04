cmake_minimum_required(VERSION 2.8)

find_package(GTest REQUIRED)

file(GLOB cpp_files gtests/*.cpp)

#message (INFO "${cpp_files}")

add_executable(yaml_inputter_gtests ${cpp_files})
target_link_libraries(yaml_inputter_gtests yaml-cpp gtest gtest_main)
target_include_directories(yaml_inputter_gtests PUBLIC include)

#add_test(NAME el_stat_prop_kit_test COMMAND el_stat_prop_kit_test)
GTEST_ADD_TESTS(yaml_inputter_gtests "" ${cpp_files})
