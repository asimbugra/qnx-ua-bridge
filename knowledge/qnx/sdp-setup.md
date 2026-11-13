# QNX SDP 8.0 setup

Facts verified from QNX 8.0 official documentation on 2026-11-13.

## Install

- Requires **QNX Software Center 2.0** (QSC). Install SDP 8.0 as a new baseline
  product; choose a **Conservative** installation policy.
  Source: GA release notes (developers.qnx.com/developers/docs/relnotes8.0), Installing QNX SDP.
- Free non-commercial access via QNX Everywhere:
  https://qnx.software/en/developers/get-started/qnx-everywhere

## Environment

- Linux host: `source <install>/qnxsdp-env.sh` (Windows: `qnxsdp-env.bat`).
  Sets QNX_HOST/QNX_TARGET etc. Default install dir convention: `~/qnx800`.
  Sources: SDP 8.0 Quick Start Guide (your_program.html); QNX Everywhere porting
  guide (porting_QNX_cross_env.html).

## Compiler

- Toolchain: GCC 12.x (12.2, binutils 2.41). Source: migration guide Toolchain page.
- `qcc`/`q++` preferred over raw gcc variants. Targets (from qcc docs):
  - x86_64: `gcc_ntox86_64` (default)
  - AArch64 LE: `gcc_ntoaarch64le` (+ `_cxx`/`_gpp` variants)
- Example: `qcc -Vgcc_ntoaarch64le -o hello hello.c`
- Direct variants exist (ntoaarch64-gcc, ntox86_64-gcc) but qcc wraps them.

## CMake

- `CMAKE_SYSTEM_NAME QNX`, compiler qcc with `-V<target>` in flags, sysroot
  QNX_TARGET. (Matches our cmake/qnx-*.cmake toolchain files.)

## Host OS constraint (important)

- QNX's own QEMU/vmware image tooling targets **Ubuntu 22.04 / 24.04** (QSTI docs
  say Ubuntu-only). Host work should happen on an Ubuntu box/WSL2.
