# qnx-ua-bridge

An OPC UA to QNX bridge for real-time industrial control.

Factory PLCs (e.g. Siemens S7-1500) expose their data over OPC UA. QNX 8.0 is the RTOS
used when timing, safety and reliability are critical. There is no mature open-source
component connecting the two. **qnx-ua-bridge** fills that gap:

- The `ua-bridge` daemon connects to an OPC UA server, subscribes to tags and keeps a
  local tag store protected by priority-inheritance mutexes.
- Tags appear as files: `cat /dev/opcua/line1/conveyor_speed` reads a live PLC value,
  `echo 1.5 > /dev/opcua/line1/setpoint` writes to the PLC.
- Real-time clients talk to the bridge over native QNX message passing and get woken
  by **pulses** when values change — no polling.
- Latency and jitter are measured with `ClockCycles()` and reported end to end.

## Status

Early development (research + skeleton). Target: QNX 8.0 on QEMU (x86_64 / aarch64le)
and Raspberry Pi 4/5. First milestone: an end-to-end slice from a host-side PLC
simulator to a tag read on QNX.

## Repository layout

```
cmake/       toolchain files + open62541 fetch
src/         bridge daemon, client library, common code
include/     public API headers
examples/    real-time control loop demo (conveyor)
tools/       plc-sim, tagmap-gen, latency-report (host side)
qnx/         buildfiles + scripts for QEMU / Raspberry Pi images
tests/       unit / target / integration / perf
docs/        architecture, build-and-run, QNX evidence
knowledge/   sourced research notes (every fact carries a source URL)
```

## License

Apache-2.0 (see [LICENSE](LICENSE)). open62541 is fetched as a dependency at a pinned
commit and is subject to its own MPL-2.0 license.
