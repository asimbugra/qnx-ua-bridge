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
