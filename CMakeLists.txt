cmake_minimum_required(VERSION 3.12.4)

project(
    LibPoly
    VERSION 0.1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(poly INTERFACE)

target_include_directories(poly INTERFACE include)

add_executable(test tests/main.cpp tests/tests.cpp)
target_compile_options(test
    PRIVATE -Wall -Wextra -Werror -pedantic)

target_include_directories(test PRIVATE tests)

target_link_libraries(test PRIVATE poly)
