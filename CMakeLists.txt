cmake_minimum_required(VERSION 3.14)
project(RCalculating)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS  "-stdlib=libc++ -std=c++1z")

add_executable(RCalculating main.cpp r.cpp)