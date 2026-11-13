# Message passing, pulses, event delivery

Facts from QNX docs (getting started + lib ref), verified 2026-11-13.

## Server side

```c
name_attach_t *attach = name_attach(NULL, "ua_bridge", 0);   // global name
// loop:
rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);
switch (msg.type) {
case _PULSE_CODE_DISCONNECT: ConnectDetach(msg.pulse.scoid); break;
case _IO_CONNECT:            MsgReply(rcvid, 0, NULL, 0); break;
case UAB_MSG_READ: ...       MsgReply(rcvid, 0, &val, sizeof(val)); break;
}
```

- Handle _IO_CONNECT when a resmgr path and name_attach share a process space.

## Client side + event (pulse) registration

```c
int coid = name_open("ua_bridge", 0);
struct sigevent ev;
SIGEV_PULSE_INIT(&ev, coid, SIGEV_PULSE_PRIO_INHERIT, UAB_PULSE_TAG_CHANGE, tagid);
MsgRegisterEvent(&ev, coid);              // converts sigevent to secure handle
MsgSend(coid, &msg, sizeof(msg), NULL, 0); // SUBSCRIBE request; reply immediate
// later, on client channel:
rcvid = MsgReceivePulse(chid, &pulse, sizeof(pulse), NULL);  // woke by pulse
```

- SIGEV_PULSE_INIT fields: (event, coid, priority, code, value).
- MsgDeliverEvent(rcvid, &event) is NON-blocking; server never inspects/modifies
  the event - kernel delivers whatever the client chose (pulse/thread/signal).
- _PULSE_CODE_DISCONNECT must be handled to clean up dead subscribers.
- QNX recommends event-driven synchronous design based on SIGEV_PULSE.

## Protocol sketch (ua_bridge channel)

- Messages: READ, WRITE, SUBSCRIBE (carries sigevent handle), UNSUBSCRIBE.
- Pulse codes (server->client): tag-changed (value in pulse value/tag lookup).
- Copy-free path: MsgRead/IOV for large payloads (later, if needed).

Sources: getting started s1_msg (MsgDeliverEvent chapter); lib_ref m/msgdeliverevent,
s/sigevent (SIGEV_PULSE_INIT macro, sigev_coid field); name_attach/name_open pages.
