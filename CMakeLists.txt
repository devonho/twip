cmake_minimum_required(VERSION 3.16)

project(controller)

add_subdirectory(controller)

include(CTest)
add_test(NAME unittests COMMAND test_controller)
set_tests_properties(unittests PROPERTIES PASS_REGULAR_EXPRESSION "100% tests passed" )