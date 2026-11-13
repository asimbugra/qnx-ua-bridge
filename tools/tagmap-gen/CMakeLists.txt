cmake_minimum_required(VERSION 3.21)
project(tagmap-gen LANGUAGES)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

add_custom_target(tagmap-gen
    COMMAND ${Python3_EXECUTABLE} -m pip install --quiet asyncua
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tagmap_gen.py
        ${CMAKE_ARG1} ${CMAKE_ARG2}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating tag map from OPC UA server"
)
