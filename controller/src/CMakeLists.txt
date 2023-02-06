cmake_minimum_required(VERSION 3.16)

project(controller)

add_executable(controller main.cpp db.cpp dbobjects.cpp)

find_package(gz-transport12)
find_package(gz-msgs9)
find_package(SQLite3)

include_directories(/usr/local/include/log4cpp)
link_directories(/usr/local/lib/)

target_include_directories(controller PUBLIC ../include gz-transport12 gz-msgs9 sqlite3)

target_link_libraries(controller PUBLIC gz-transport12 gz-msgs9 sqlite3 liblog4cpp.so)
