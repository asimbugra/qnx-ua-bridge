cmake_minimum_required(VERSION 3.21)
project(plc-sim LANGUAGES)

option(UAB_PLCSIM_WITH_PYTHON "Build Python plc-sim (requires asyncua)" ON)

if(UAB_PLCSIM_WITH_PYTHON)
    find_package(Python3 REQUIRED COMPONENTS Interpreter)
    # asyncua is a pip dep; installed at build time
    add_custom_target(plc-sim-python
        COMMAND ${Python3_EXECUTABLE} -m pip install --quiet asyncua
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/plc_sim.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Starting plc-sim OPC UA server on opc.tcp://0.0.0.0:4840"
    )
    add_custom_target(plc-sim DEPENDS plc-sim-python)
endif()
