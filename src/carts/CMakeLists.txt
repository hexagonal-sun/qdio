cmake_minimum_required(VERSION 2.8.11)

project(carts)

set(CARTS_SRCS cartButton.cpp
               cartsWindow.cpp)

add_library(carts STATIC ${CARTS_SRCS})
target_link_libraries(carts Qt5::Widgets Qt5::Multimedia)
