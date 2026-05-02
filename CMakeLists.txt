cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(
    p1-meter
    VERSION 1.0.0
    DESCRIPTION "Parses P1 telegram and forwards to a server in json-format"
    HOMEPAGE_URL "https://github.com/thorstink/p1"
    LANGUAGES CXX
)

option(BUILD_TESTS FALSE)
add_executable(p1-meter main.cpp)
