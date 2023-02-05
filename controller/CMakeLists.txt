cmake_minimum_required(VERSION 3.22)

project(controller)

add_executable(controller main.cpp db.cpp)

find_package(gz-transport12)
find_package(gz-msgs9)
find_package(SQLite3)

target_include_directories(controller PUBLIC gz-transport12 gz-msgs9 sqlite3)

target_link_libraries(controller PUBLIC gz-transport12 gz-msgs9 sqlite3)