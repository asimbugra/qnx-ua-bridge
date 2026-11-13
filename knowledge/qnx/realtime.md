# Real-time: priorities, timers, clocks, PI mutexes

Facts from QNX 8.0 documentation, verified 2026-11-13 (ClockCycles exact API
signature to be re-verified against lib_ref when implementing).

## Thread priorities / scheduling

- SCHED_FIFO with pthread_setschedparam; QNX priorities 1..255 (highest wins).
- QNX message passing preserves sender priority into the server thread
  (priority inheritance through channels) - the UA client thread replying to a
  high-priority control client inherits its urgency. (QNX kernel docs; confidence:
  documented - cite sys_arch kernel IMPLEMENT page in qnx-evidence.md.)

## Timers

- timer_create(CLOCK_MONOTONIC, &event, &timerid) with SIGEV_PULSE event ->
  periodic pulses drive the control loop (10 ms default in conveyor example).
- timer_settime with it_interval for periodic firing.

## High-resolution time

- ClockCycles() returns free-running 64-bit counter; convert via
  SYSPAGE_ENTRY(qtime)->cycles_per_sec (per-boot value, not compile-time).
- Use for: PLC source timestamp -> bridge receipt -> client pulse receipt deltas.

## Priority-inheritance mutexes

- QNX pthread_mutex with PTHREAD_PRIO_INHERIT protocol guards the tag store;
  prevents priority inversion between the UA network thread (low) and control
  loops (high) sharing tag values. Default QNX mutexes already give PI when
  contention occurs (kernel-managed); explicit protocol is the documented-safe form.

## Suggested layout (ADR-004 will finalize)

- UA client thread: priority ~20 (network, non-RT)
- resmgr/ipc threads: ~30 (client-facing)
- control loop (example): 50 (SCHED_FIFO, timer pulse driven)
- watchdog: 10
