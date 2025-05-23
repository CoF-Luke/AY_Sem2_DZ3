cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(dz3)

add_executable(main main.cpp)

add_library(fun STATIC functions.cpp classes.cpp)

target_link_libraries(main fun)
















