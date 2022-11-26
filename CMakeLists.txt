cmake_minimum_required(VERSION 3.22)
project(dns_lookup)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(FILTER SOURCES EXCLUDE REGEX ".*main\\.cpp$")

add_subdirectory(vendor/googletest)
add_subdirectory(test)

add_executable(
    ${CMAKE_PROJECT_NAME}
    ${SOURCES}
    src/main.cpp
)
