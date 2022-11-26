cmake_minimum_required(VERSION 3.22)

set(TEST ${CMAKE_PROJECT_NAME}_tests)

file(GLOB_RECURSE TEST_SOURCES ${PROJECT_SOURCE_DIR} true *.h *.cpp)

add_executable(${TEST} ${TEST_SOURCES} ${SOURCES})

target_link_libraries(${TEST} gtest_main)

add_test(NAME ${TEST} COMMAND ${TEST})