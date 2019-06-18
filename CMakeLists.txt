cmake_minimum_required(VERSION 3.8)
project(ReducedSum)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCES reducedsum.cpp main.cpp)

add_executable(ReducedSum ${SOURCES})

option(BUILD_TEST "Build gtest for localMinimum project" ON)

if (${BUILD_TEST})
    enable_testing()
    add_subdirectory(test)
endif()