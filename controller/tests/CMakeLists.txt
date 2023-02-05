cmake_minimum_required(VERSION 3.22)

project(controller)

find_package(Catch2 REQUIRED)

add_executable(test_controller test_db.cpp)

