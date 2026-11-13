# ADR-004: Thread model and priorities

Date: 2026-11-13
Status: accepted (review after Phase 2 measurements)

## Context

The bridge mixes a network stack (open62541 iterate loop) with client-facing IPC
and RT consumers. QNX message passing propagates/ inherits priority, so server
thread placement directly affects RT behavior.

## Decision

Threads inside ua-bridge (all in one process, one channel):

| Thread | Sched | Prio | Role |
|---|---|---|---|
| ua-client | SCHED_OTHER | nice 0 (≈10 FIFO-equiv) | open62541 connect/iterate, subscriptions |
| watchdog | SCHED_FIFO | 12 | reconnect backoff, health |
| resmgr pool | SCHED_OTHER | default pool | /dev/opcua file ops (blocking tolerated) |
| ipc-server | SCHED_FIFO | 30 | MsgReceive loop for ua_bridge channel |
| (clients) | SCHED_FIFO | 40-55 | e.g. conveyor_ctrl at 50 |

- Tag store: single pthread mutex with PTHREAD_PRIO_INHERIT; ua-client and
  ipc-server both take it briefly (copy in/out, no callbacks under lock).
- Value-change notifications: ipc-server delivers pulses via MsgDeliverEvent
  (non-blocking); pulse priority = subscribing client's choice
  (SIGEV_PULSE_PRIO_INHERIT pattern).
- Rule: no open62541 call under the tag-store lock; no blocking call in
  ipc-server loop (writes to PLC are queued to ua-client via a local pulse).

## Consequences

- Priority inheritance through the channel keeps a prio-50 control client's
  READ served ahead of network churn - the core determinism claim, measurable.
- Revisit after Phase 2 latency data.
