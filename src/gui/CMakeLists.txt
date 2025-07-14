cmake_minimum_required(VERSION 3.10)
project(Program)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_Release "-O3")
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_executable(Program
        main.cpp
)

target_include_directories(Program PRIVATE
    ${CMAKE_HOME_DIRECTORY}/headers
    ${CMAKE_HOME_DIRECTORY}/src
)

target_link_directories(Program PRIVATE
        ${CMAKE_HOME_DIRECTORY}/dependencies/dynamic
        ${CMAKE_HOME_DIRECTORY}/dependencies/static
)

target_link_libraries(Program PRIVATE
    raylib
    WaveFunctionCollapse
)
