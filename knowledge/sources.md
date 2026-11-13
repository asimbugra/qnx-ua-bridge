# Sources

Every technical fact recorded in knowledge/ traces to an entry here.
Format: `- fact -- source: URL -- confidence: verified|documented|assumed -- date`

## Hackathon

- Full official rules text (dates, requirements, categories, judging, prizes) -- source: https://qnx.devpost.com/rules -- confidence: verified -- 2026-11-13
- Submission period opens Nov 2 2026 11:00 ET / closes Dec 15 2026 14:00 ET -- source: https://qnx.devpost.com/ + rules page -- confidence: verified -- 2026-11-13
- QEMU and Raspberry Pi 5 acceptable targets; SDP free for non-commercial use -- source: https://qnx.devpost.com/ -- confidence: verified -- 2026-11-13
- Free SDP 8.0 access URL -- source: https://qnx.software/en/developers/get-started/qnx-everywhere (cited from rules) -- confidence: verified -- 2026-11-13

## open62541 on QNX

- PR #8702 merged 2026-11-10T22:21:59Z, merge SHA 667acbc69132d3ba5b6db17be8002cb121849d41, 4 files +17/-4 -- source: GitHub API repos/open62541/open62541/pulls/8702 -- confidence: verified -- 2026-11-13
- PR #8702 diff details (sys/queue.h under __QNX__; link socket; pthread/rt in libc) -- source: GitHub API pulls/8702/files -- confidence: verified -- 2026-11-13
- Latest release v1.5.10 (2026-10-30) predates the QNX merge; fixes exist only on master -- source: GitHub API releases/latest + tags -- confidence: verified -- 2026-11-13
- QNX issues #339 #493 #594 #787 #5986 all closed; prior QNX PRs #995 #6966 #6967 closed unmerged -- source: GitHub API issues + PR search -- confidence: verified -- 2026-11-13

## QNX 8.0 platform

- OpenSSL 3.0 (default; 3.5 also) ships with SDP 8.0; libcrypto.so.3/libssl.so.3; qcrypto plugin -- source: https://www.qnx.com/developers/docs/8.0/com.qnx.doc.qnxsdp.migration/topic/security.html + relnotes8.0 + System Security Guide -- confidence: verified -- 2026-11-13
- IFS buildfile model, mkifs autoso for shared libs; libc.so required in images -- source: https://www.qnx.com/developers/docs/8.0/com.qnx.doc.neutrino.building/ (shared libraries, buildfiles pages) -- confidence: documented -- 2026-11-13
- SDP is a cross-compiling environment; BSPs provide board files; io-sock stack based on FreeBSD 13.2 -- source: QNX 8.0 building guide overview + GA release notes -- confidence: documented -- 2026-11-13

## S7-1500

- OPC UA server on S7-1500 requires a CPU-class runtime license (small/medium/large mapping) -- source: https://docs.tia.siemens.cloud/ "License for OPC UA" -- confidence: verified -- 2026-11-13

## QNX platform (knowledge/qnx/)

- qnxsdp-env.sh location + qcc -V usage; targets gcc_ntox86_64 (default), gcc_ntoaarch64le -- source: https://www.qnx.com/developers/docs/8.0/com.qnx.doc.qnxsdp.quickstart/topic/your_program.html + utilities q/qcc.html -- confidence: verified -- 2026-11-13
- GCC 12.x toolchain (12.2/binutils 2.41) in SDP 8.0 -- source: https://www.qnx.com/developers/docs/8.0/com.qnx.doc.qnxsdp.migration/topic/toolchain.html -- confidence: verified -- 2026-11-13
- SDP install via QNX Software Center 2.0, Conservative policy; free QNX Everywhere access URL -- source: https://www.qnx.com/developers/docs/relnotes8.0/com.qnx.doc.release_notes/topic/sdp8_rn.html -- confidence: verified -- 2026-11-13
- QSTI prebuilt QEMU image package (com.qnx.qnx800.quickstart.qemu), Ubuntu 22.04/24.04 host only -- source: https://www.qnx.com/developers/docs/qnxeverywhere/rel_notes.html -- confidence: verified -- 2026-11-13
- mkqnximage --type=qemu --arch=x86_64|aarch64le; snippet prefixes ifs_files/system_files/data_files/ifs_env; headless output qemu.out -- source: https://www.qnx.com/developers/docs/8.0/com.qnx.doc.neutrino.utilities/topic/m/mkqnximage.html -- confidence: verified -- 2026-11-13
- Pi 5 BSP (BCM2712, com.qnx.qnx800.bsp.hw.raspberrypi_bcm2712_rpi5 build 568), 4GB/8GB; rebuild IFS recommended; CTI on gitlab qnx/custom-target-image-builds -- source: BSP8.0 docs (rel_sdp80.bsp.broadcom.rpi5.bcm2712, bsp_build, bsp_hw, about) -- confidence: verified -- 2026-11-13
- resmgr skeleton (dispatch_create_channel, iofunc_func_init, resmgr_attach, dispatch_block loop); secpol_resmgr_attach recommendation -- source: https://www.qnx.com/developers/docs/8.0/com.qnx.doc.neutrino.getting_started/topic/s1_resmgr_the_resource_manager_library.html + security guide write_resource_manager -- confidence: verified -- 2026-11-13
- MsgDeliverEvent non-blocking, server must not modify event; SIGEV_PULSE_INIT(event, coid, priority, code, value); MsgRegisterEvent for secure events; _PULSE_CODE_DISCONNECT handling -- source: getting_started s1_msg_MsgDeliverEvent + lib_ref m/msgdeliverevent, s/sigevent -- confidence: verified -- 2026-11-13
- Third-party corroboration of QEMU workflow (mkqnximage qemu x86_64, ssh sync, ctest via CMAKE_CROSSCOMPILING_EMULATOR) -- source: https://pypi.org/project/qnx-porter/ -- confidence: documented -- 2026-11-13
