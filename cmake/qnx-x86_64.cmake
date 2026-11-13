# Toolchain file for QNX SDP 8.0, x86_64 (primary QEMU target).
# Source the QNX SDP environment first:
#   . <qnx-sdp-install>/qnxsdp-env.sh
set(CMAKE_SYSTEM_NAME QNX)
set(CMAKE_SYSTEM_VERSION 8.0)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(arch gcc_ntox86_64)

set(CMAKE_C_COMPILER   qcc)
set(CMAKE_C_FLAGS      "-V${arch}")
set(CMAKE_CXX_COMPILER q++)
set(CMAKE_CXX_FLAGS    "-V${arch}")

set(CMAKE_FIND_ROOT_PATH "$ENV{QNX_TARGET}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
