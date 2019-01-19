cmake_minimum_required(VERSION 2.8.11)

project(qdio)

set(CMAKE_CXX_STANDARD 14)

set(SUBPROJECTS sessions rest carts)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5Multimedia)
find_package(Qt5Sql)

include_directories(${SUBPROJECTS})

foreach(SUBPROJECT ${SUBPROJECTS})
    add_subdirectory(${SUBPROJECT})
endforeach()

set(QDIO_SOURCES main.cpp)

add_executable(qdio ${QDIO_SOURCES})

target_link_libraries(qdio
                      ${SUBPROJECTS}
                      Qt5::Widgets
                      Qt5::Network
                      Qt5::Multimedia
                      Qt5::Sql)
