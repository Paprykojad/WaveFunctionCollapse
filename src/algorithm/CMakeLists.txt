cmake_minimum_required(VERSION 3.10)
project(WaveFunctionCollapse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_Release "-O3")
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_library(WaveFunctionCollapse STATIC
        ColorTable.cpp
        Learner.cpp
        RandomMachine.cpp
        Color.cpp
        ColorCounter.cpp

)

target_include_directories(WaveFunctionCollapse PRIVATE
        ${CMAKE_SOURCE_DIR}/headers
)

target_link_directories(WaveFunctionCollapse PRIVATE
        ${CMAKE_HOME_DIRECTORY}/dependencies/dynamic
        ${CMAKE_HOME_DIRECTORY}/dependencies/static
)

target_link_libraries(WaveFunctionCollapse PRIVATE
)
