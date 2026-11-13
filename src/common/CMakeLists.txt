cmake_minimum_required(VERSION 3.21)

# Common library: JSON config parser, type conversions
add_library(uab_common STATIC
    uab_json.c
    vendor/jsmn/jsmn.h
)
target_include_directories(uab_common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/jsmn
)
# No external dependencies
