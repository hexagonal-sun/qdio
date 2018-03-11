cmake_minimum_required(VERSION 2.8.11)

project(qdio)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5Multimedia)

add_executable(qdio main.cpp cartsWindow.cpp cartButton.cpp restRequest.cpp authDialog.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(qdio Qt5::Widgets Qt5::Network Qt5::Multimedia)