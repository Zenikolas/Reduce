find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(stringNumberTest stringnumbertest.cpp)

message("Found gtest libs: ${GTEST_LIBRARIES}")
message("Found gtest libs: ${GTEST_BOTH_LIBRARIES}")
message("Found gtest libs: ${GTEST_FOUND}")
target_link_libraries(stringNumberTest ${GTEST_BOTH_LIBRARIES} pthread)

gtest_discover_tests(stringNumberTest)