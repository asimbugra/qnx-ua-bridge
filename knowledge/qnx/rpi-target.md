# Raspberry Pi 5 target

Facts verified 2026-11-13 from QNX SDP 8.0 BSP documentation.

## Official BSP

- "QNX SDP 8.0 BSP for Raspberry Pi 5" (Broadcom BCM2712). Package:
  com.qnx.qnx800.bsp.hw.raspberrypi_bcm2712_rpi5 (build 568, v0.4.0).
- Supports Pi 5 boards with 4GB and 8GB RAM.
- Sources: BSP release notes + BSP user guide (developers.qnx.com/developers/docs/BSP8.0/).

## Image build

- BSP contains prebuilt IFS images for quick start, but QNX recommends rebuilding
  the IFS on the host so it matches your dev environment.
- Build via Momentics IDE or command line; drivers not needed are commented out in
  the buildfile (e.g. wifi via io-sock) - uncomment and rebuild to enable.
- CTI (Custom Target Image) project supports Pi 4, Pi 5, and QEMU x86_64:
  gitlab.com/qnx/custom-target-image-builds (CTI-8.0.5r1 latest at time of writing).

## Boot

- Write IFS to a (micro)SD card, adjust config.txt to boot the QNX IFS image.
- Swap SD cards to switch between Linux and QNX on the same board - no sharing.

## Plan for this project

- QEMU = daily dev loop; Pi 5 = final demo target (real hardware determinism
  numbers for the demo video).
