cmake_minimum_required(VERSION 3.22)
project(dns_lookup)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(HEADERS
    include/common/exception.h
    include/common/buffer.h
    include/dns/dns_utilities.h
    include/dns/dns_question.h
    include/dns/types.h
    include/network/net_utilities.h
    include/network/endpoint.h
    include/network/socket.h
)

set(SOURCES
    src/main.cpp
    src/common/buffer.cpp
    src/dns/dns_question.cpp
    src/network/endpoint.cpp
    src/network/socket.cpp
)

add_executable(
    ${CMAKE_PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)
