cmake_minimum_required(VERSION 2.8.11)

project(sessions)

set(SESSIONS_SRCS authDialog.cpp
                  showDialog.cpp
                  sessionManager.cpp)

add_library(sessions STATIC ${SESSIONS_SRCS})
target_link_libraries(sessions Qt5::Network Qt5::Widgets Qt5::Multimedia)
