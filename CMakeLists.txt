cmake_minimum_required(VERSION 3.28)
project(lecpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler warnings (GCC 14 / Clang 19)
add_compile_options(
    -Wall -Wextra -Wpedantic -Werror
    -Wshadow -Wconversion -Wsign-conversion
    -Wnon-virtual-dtor -Wold-style-cast
    -Wcast-align -Wunused -Woverloaded-virtual
    -Wnull-dereference -Wdouble-promotion
    -Wformat=2 -Wimplicit-fallthrough
)

# Debug build: enable sanitizers
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()

add_executable(main src/main.cpp)
add_executable(containers_worksheet src/containers_worksheet.cpp)
add_executable(20_stl_algorithms src/20_stl_algorithms_worksheet.cpp)
add_executable(21_for_each_deep_dive src/21_for_each_deep_dive.cpp)
add_executable(21_for_each_teach src/21_for_each_teach.cpp)
add_executable(21_for_each_puzzle src/21_for_each_puzzle.cpp)
