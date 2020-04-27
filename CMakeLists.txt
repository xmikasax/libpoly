cmake_minimum_required(VERSION 3.12.4)

project(
    LibPoly
    VERSION 0.1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(
    poly
    SHARED
    src/monomial.cpp
    src/utils.cpp
)

target_include_directories(poly PUBLIC include)
target_include_directories(poly PRIVATE src)

target_compile_options(poly
    PRIVATE -Wall -Wextra -Werror)

add_executable(test tests/main.cpp tests/tests.cpp)
target_include_directories(test PRIVATE tests/)

target_link_libraries(test PRIVATE poly)
