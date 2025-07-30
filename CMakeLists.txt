cmake_minimum_required(VERSION 3.10)
project(WaveFunctionCollapse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_Release "-O3")
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_subdirectory(tests)
add_subdirectory(src/gui)
add_subdirectory(src/algorithm)
add_subdirectory(src/program)
