cmake_minimum_required(VERSION 3.10)
project(Tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_Release "-O3")
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# Enable testing
enable_testing()

# Create the test executable
add_executable(tests
        tests.cpp
        ColorTableTests.cpp
        LearnerTests.cpp
)

target_include_directories(tests PRIVATE
        ${CMAKE_HOME_DIRECTORY}/headers
        ${CMAKE_HOME_DIRECTORY}/src
)

target_link_directories(tests PRIVATE
        ${CMAKE_HOME_DIRECTORY}/dependencies/static
        ${CMAKE_HOME_DIRECTORY}/dependencies/dynamic
)

target_link_libraries(tests PRIVATE
        WaveFunctionCollapse
        raylib
)

# Add the test - this runs the entire executable as one test
add_test(NAME tests COMMAND tests)
