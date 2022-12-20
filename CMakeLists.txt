cmake_minimum_required(VERSION 3.22)
project(dns_lookup)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(FILTER SOURCES EXCLUDE REGEX ".*main\\.cpp$")

add_subdirectory(vendor/googletest)
add_subdirectory(vendor/gflags)
add_subdirectory(test)

add_executable(
    ${CMAKE_PROJECT_NAME}
    ${SOURCES}
    src/main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} gflags)