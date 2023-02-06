cmake_minimum_required(VERSION 3.16)

project(controller)

find_path(CONTROLLER_INCLUDE NAMES db.h PATHS ../include)
find_path(CONTROLLER_SOURCE NAMES db.cpp PATHS ../src)

find_package(SQLite3)

add_executable(test_controller 
    test_db.cpp 
    ${CONTROLLER_SOURCE}/db.cpp
    ${CONTROLLER_SOURCE}/dbobjects.cpp)

target_include_directories(test_controller PRIVATE ${CONTROLLER_INCLUDE})

target_link_libraries(test_controller sqlite3)