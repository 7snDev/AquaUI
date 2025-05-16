cmake_minimum_required(VERSION 3.14)
project(AquaUI)
set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(TINYXML2 REQUIRED tinyxml2)

include_directories(${TINYXML2_INCLUDE_DIRS})
link_directories(${TINYXML2_LIBRARY_DIRS})

add_executable(xmlc compiler.cpp)

target_link_libraries(xmlc ${TINYXML2_LIBRARIES})
