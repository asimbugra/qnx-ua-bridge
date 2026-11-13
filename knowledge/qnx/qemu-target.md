# QEMU target

Facts verified 2026-11-13 from QNX 8.0 documentation and release notes.

## Two supported routes

### 1. Quick Start Target Image (QSTI) - fastest start

- Prebuilt QEMU image package in QNX Software Center: Available -> SDP ->
  Reference Images -> "QNX SDP 8.0 Quick Start Target Image for QEMU"
  (package com.qnx.qnx800.quickstart.qemu).
- **Ubuntu 22.04/24.04 only** (host constraint).
- Source: QNX Everywhere release notes (developers.qnx.com/developers/docs/qnxeverywhere/rel_notes.html)

### 2. mkqnximage - custom VM images

- `mkqnximage --type=qemu|vmware|vbox|qvm --arch=x86_64|aarch64le` builds a VM
  image from SDP components + repos. Snippet files customize the image:
  - `ifs_files*` (mkifs buildfile format, IFS additions)
  - `system_files*` / `data_files*` (mkqnx6fsimg format, partition contents)
  - `ifs_env` (startup script env/symlinks)
- Supported combos (mkqnximage docs): QEMU on Ubuntu -> x86-64 AND AArch64;
  vmware/vbox on Windows -> x86-64.
- Headless mode console goes to output/qemu.out; `--run` launches.
- Source: QNX 8.0 Utilities Reference, mkqnximage page.

## Deploy workflow (from the Quick Start guide)

1. `source qnxsdp-env.sh`
2. `qcc -Vgcc_ntox86_64 -o ua-bridge ...` (via our CMake toolchain file)
3. `scp ua-bridge root@<vm-ip>:/tmp` (VM gets an IP; e.g. 192.168.91.128 in docs)
4. Run on the VM console or over SSH.

## Network notes

- QEMU image runs io-sock (FreeBSD 13.2-based stack) per GA release notes.
- Default QSTI image: check `ifconfig` on target; docs use ssh root@IP directly.

## Reference: qnx-porter (third-party, independent evidence)

- pypi qnx-porter README: tested on QNX 8.0 x86_64 QEMU via mkqnximage
  (--type=qemu --arch=x86_64), syncs build over ssh (tar), runs ctest on target
  through CMAKE_CROSSCOMPILING_EMULATOR. Confirms our intended workflow is sane.
