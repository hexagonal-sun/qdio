cmake_minimum_required(VERSION 2.8.11)

project(qdio_etc)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)
find_package(Qt5Core)
find_package(Qt5Sql)

add_executable(passwordUpdater passwordUpdater.cpp)
target_link_libraries(passwordUpdater Qt5::Core Qt5::Sql)
