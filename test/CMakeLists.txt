find_package(GTest REQUIRED)

include_directories(${PROJECT_SOURCE_DIR} ${GTest_INCLUDE_DIRS})

add_executable(stringNumberTest stringnumbertest.cpp)

target_link_libraries(stringNumberTest ${GTest_LIBRARIES} pthread)

gtest_discover_tests(stringNumberTest)