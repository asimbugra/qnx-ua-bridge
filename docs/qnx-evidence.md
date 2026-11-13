# QNX technology evidence

Reference list for judges: every QNX-specific API used by this project, with
the file and function that uses it. Updated as code lands.

| # | QNX technology | API | Where | Status |
|---|---|---|---|---|
| 1 | Resource manager | resmgr_attach, iofunc_func_init, iofunc_attr_init | src/bridge/resmgr.c | planned |
| 2 | Resource manager | custom io_read handler (tag values as text) | src/bridge/resmgr.c | planned |
| 3 | Resource manager | custom io_write handler (writes to PLC) | src/bridge/resmgr.c | planned |
| 4 | Resource manager | directory tree under /dev/opcua | src/bridge/resmgr.c | planned |
| 5 | Message passing | name_attach/name_open ("ua_bridge") | src/bridge/ipc_server.c, src/lib | planned |
| 6 | Message passing | MsgReceive/MsgReply protocol READ/WRITE/SUBSCRIBE | src/bridge/ipc_server.c | planned |
| 7 | Pulses | SIGEV_PULSE_INIT + MsgDeliverEvent for value-change notify | src/bridge/ipc_server.c | planned |
| 8 | Priority inheritance | PTHREAD_PRIO_INHERIT mutex in tag store | src/bridge/tag_store.c | planned |
| 9 | Timers | timer_create + periodic pulse (control loop) | examples/conveyor_ctrl | planned |
| 10 | Clocks | ClockCycles + SYSPAGE_ENTRY(qtime)->cycles_per_sec | src/bridge/metrics.c | planned |
| 11 | Scheduling | SCHED_FIFO priorities per ADR-004 | throughout | planned |
| 12 | System image | IFS buildfile including ua-bridge | qnx/buildfiles/ | planned |

Each row gains a "verified on target" note (QEMU/Pi 5 + date) as it lands.
