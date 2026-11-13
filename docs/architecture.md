# Architecture

Condensed working document; expands as components land.

## Big picture

```
PLC (S7-1500 OPC UA server, or tools/plc-sim on the host)
        |  OPC UA over TCP 4840 (optionally encrypted)
        v
QNX 8.0 target (QEMU / Raspberry Pi 4/5)
  ua-bridge daemon
    |- UA client thread (open62541): subscriptions / monitored items
    |- Tag store (priority-inheritance mutex, per-tag timestamps)
    |- Resource manager -> /dev/opcua/<group>/<tag>
    |- Message-passing channel ("ua_bridge"): MsgReceive / MsgReply + pulses
    |- Watchdog + reconnect with exponential backoff
    \- Metrics (ClockCycles-based latency / jitter)
  Clients
    |- shell: cat / echo on /dev/opcua/...
    |- libuabridge (C API) for RT control loops
    \- uabridge-top live monitor
```

## QNX-specific technologies

| Technology | Where it lands |
|---|---|
| Resource manager (`resmgr_attach`, `iofunc_*`) | `src/bridge/resmgr.c` — tags as files under `/dev/opcua` |
| Message passing (`name_attach`/`name_open`, `MsgReceive`/`MsgReply`) | `src/bridge/ipc_server.c` |
| Pulses / event delivery (`MsgDeliverEvent`, `SIGEV_PULSE`) | value-change notifications without polling |
| Priority-inheritance mutexes | tag store protection (`src/bridge/tag_store.c`) |
| QNX timers (`timer_create` + pulse), `ClockCycles()` | periodic control loop, high-res latency measurement |
| `SCHED_FIFO` thread priorities | separating the UA network thread from control threads |
| QNX buildfile / system image | `qnx/buildfiles` for QEMU and Raspberry Pi images |

File-and-function evidence for each row: `docs/qnx-evidence.md` (added as components land).
