cmake_minimum_required(VERSION 3.16)

project(controller)

find_path(CONTROLLER_INCLUDE NAMES db.h PATHS ../include)
find_path(CONTROLLER_SOURCE NAMES db.cpp PATHS ../src)

find_package(SQLite3 REQUIRED)
find_package(Threads REQUIRED)
find_package(gz-msgs9 REQUIRED)

add_executable(test_controller 
    test_db.cpp 
    test_queue.cpp 
    ${CONTROLLER_SOURCE}/db.cpp
    ${CONTROLLER_SOURCE}/dbobjects.cpp
    ${CONTROLLER_SOURCE}/queue.cpp
    )

target_include_directories(test_controller PRIVATE ${CONTROLLER_INCLUDE})

target_link_libraries(test_controller sqlite3 Threads::Threads gz-msgs9)