find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(reducedSumTest reducedSumTest.cpp ${PROJECT_SOURCE_DIR}/reducedsum.cpp)

if (${GTEST_FOUND})
    message("Found gtest headers: ${GTEST_INCLUDE_DIRS}")
    message("Found gtest libs: ${GTEST_BOTH_LIBRARIES}")
else()
    message(FATAL_ERROR "Gtest library wasn't found!")
endif()

target_link_libraries(reducedSumTest ${GTEST_BOTH_LIBRARIES} pthread)

gtest_discover_tests(reducedSumTest)