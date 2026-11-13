# Build and run

Toolchain and target matrix (per ADR-005):

| Role | Target | Toolchain |
|---|---|---|
| Daily development | QEMU x86_64, QNX 8.0 | QNX SDP 8.0 (qcc, gcc_ntox86_64) |
| Final demo | Raspberry Pi 5, QNX 8.0 | QNX SDP 8.0 (qcc, gcc_ntoaarch64le) + RPi 5 BSP |
| Host tools / unit tests | Linux (Ubuntu 22.04/24.04) | system GCC |

## Prerequisites

1. QNX SDP 8.0 (free for non-commercial use via
   [QNX Everywhere](https://qnx.software/en/developers/get-started/qnx-everywhere)).
   Install through QNX Software Center with a Conservative policy.
2. Host: Ubuntu 22.04 or 24.04 (required by QNX VM tooling).
3. CMake >= 3.21, ninja or make, Python 3 (for host tools).

## Host tools and unit tests (no QNX required)

```sh
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build
```

## PLC simulator (host)

```sh
python3 -m venv .venv && source .venv/bin/activate
pip install asyncua
python tools/plc-sim/plc_sim.py       # serves opc.tcp://0.0.0.0:4840
```

Generate a tag map from the running simulator (or any OPC UA server):

```sh
python tools/tagmap-gen/tagmap_gen.py opc.tcp://127.0.0.1:4840 tags.json
```

## Cross-compiling the bridge for QNX 8.0 (QEMU x86_64)

```sh
source <sdp-install>/qnxsdp-env.sh
cmake -B build-qnx -S . \
    -DCMAKE_TOOLCHAIN_FILE=cmake/qnx-x86_64.cmake \
    -DCMAKE_BUILD_TYPE=Release
cmake --build build-qnx
```

The bridge daemon lands in `build-qnx/src/bridge/ua-bridge` once Phase 1
targets are wired in.

## Running on QEMU (Quick Start Target Image)

1. In QNX Software Center install: **QNX SDP 8.0 Quick Start Target Image for QEMU**
   (package `com.qnx.qnx800.quickstart.qemu`).
2. Boot the VM and note its IP (console shows it; docs default: 192.168.91.128).
3. Deploy: `scp build-qnx/src/bridge/ua-bridge root@<vm-ip>:/tmp/`
4. Run on the target: `ua-bridge tags.json` (reads the tag map, connects back
   to the host simulator).

## Running on Raspberry Pi 5

1. Install the **QNX SDP 8.0 BSP for Raspberry Pi 5** package via QNX Software
   Center; rebuild the IFS on the host (BSP docs: BSP8.0 raspberrypi_bcm2712_rpi5).
2. Write the IFS to a dedicated microSD card (the card is swappable; the
   board's Linux card stays untouched).
3. `scp` the binary and run as above once networking is up on the target.

## Versions used

- QNX SDP 8.0 (GA), GCC 12.2 toolchain from the SDP
- open62541 at pinned commit 667acbc... (see cmake/open62541.cmake)
- CMake 3.21+
