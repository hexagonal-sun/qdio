cmake_minimum_required(VERSION 2.8.11)

project(rest)

set(REST_SRCS restRequest.cpp)

add_library(rest STATIC ${REST_SRCS})
target_link_libraries(rest Qt5::Network Qt5::Widgets)
