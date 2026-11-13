# ADR-005: Primary and demo targets

Date: 2026-11-13
Status: accepted

## Context

QNX supports QEMU (x86_64, aarch64le) and Raspberry Pi 5 (BSP bcm2712). Developer
hardware on hand: Raspberry Pi 5 (currently running Linux on its own card) and a
PC host. QSTI/QEMU tooling requires Ubuntu 22.04/24.04 host.

## Decision

- **Daily development target: QEMU x86_64** (QSTI prebuilt image, then mkqnximage
  custom image once we need ua-bridge baked in).
- **Final demo target: Raspberry Pi 5** (aarch64le BSP image on a separate SD
  card; the Linux card stays untouched).
- Both toolchains stay maintained (cmake/qnx-x86_64.cmake, cmake/qnx-aarch64le.cmake);
  Pi 4 explicitly out of scope.

## Consequences

- Fast inner loop on QEMU; real-hardware jitter numbers for the demo video
  (stronger evidence than emulator numbers).
- Pi 5 SD card image build needs the BSP from QNX Software Center once SDP is up.
- Host must be Ubuntu 22.04/24.04 (or WSL2) for mkqnximage - confirmed constraint.
