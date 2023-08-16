cmake_minimum_required(VERSION 3.16.3)

project(BigInt)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_FLAGS "-g -fprofile-arcs -ftest-coverage")

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(googletest)
