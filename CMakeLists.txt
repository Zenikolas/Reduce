cmake_minimum_required(VERSION 3.14)
project(ReducedSum)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_COMPILER  "clang++")
set(CMAKE_CC_COMPILER  "clang")
if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8")
    message(FATAL_ERROR "Requires clang++ version >= 8.0.0 with c++17 support")
endif()

set(CMAKE_CXX_FLAGS  "-stdlib=libc++ -std=c++1z")

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCES reducedsum.cpp stringnumber.cpp main.cpp)
add_executable(ReducedSum ${SOURCES})

enable_testing()

add_subdirectory(test)