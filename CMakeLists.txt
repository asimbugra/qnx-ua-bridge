cmake_minimum_required(VERSION 3.21)
project(qnx-ua-bridge
    VERSION 0.1.0
    DESCRIPTION "OPC UA to QNX bridge for real-time industrial control"
    LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(UAB_BUILD_TESTS    "Build tests"      ON)
option(UAB_BUILD_TOOLS    "Build host tools" ON)
option(UAB_BUILD_EXAMPLES "Build examples"   ON)

if(CMAKE_SYSTEM_NAME STREQUAL "QNX")
    message(STATUS "Cross-compiling for QNX 8.0 (${CMAKE_SYSTEM_PROCESSOR})")
endif()

# Target components are wired in as they land:
# include(cmake/open62541.cmake)
# add_subdirectory(src)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "QNX" AND UAB_BUILD_TOOLS)
    add_subdirectory(tools)
endif()

if(UAB_BUILD_TESTS)
    enable_testing()
    if(NOT CMAKE_SYSTEM_NAME STREQUAL "QNX")
        add_subdirectory(tests/unit)
    endif()
endif()
