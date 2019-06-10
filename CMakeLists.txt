cmake_minimum_required(VERSION 3.14)
project(ReducedSum)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS  "-stdlib=libc++ -std=c++1z")

set(SOURCES reducedsum.cpp stringnumber.cpp)
add_executable(ReducedSum main.cpp ${SOURCES})