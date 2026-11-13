# Toolchain file for QNX SDP 8.0, aarch64le (Raspberry Pi 4/5, ARM QEMU).
# Source the QNX SDP environment first:
#   . <qnx-sdp-install>/qnxsdp-env.sh
set(CMAKE_SYSTEM_NAME QNX)
set(CMAKE_SYSTEM_VERSION 8.0)
set(CMAKE_SYSTEM_PROCESSOR aarch64le)

set(arch gcc_ntoaarch64le)

set(CMAKE_C_COMPILER   qcc)
set(CMAKE_C_FLAGS      "-V${arch}")
set(CMAKE_CXX_COMPILER q++)
set(CMAKE_CXX_FLAGS    "-V${arch}")

set(CMAKE_FIND_ROOT_PATH "$ENV{QNX_TARGET}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
