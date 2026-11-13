# Judging criteria & prize targets

Source: Official Rules section 6, https://qnx.devpost.com/rules (verified 2026-11-13)

Stage One (pass/fail): does the project fit the theme and reasonably apply QNX 8.0?

Stage Two - four equally weighted criteria:

1. **Technological Implementation** - how well built, how effectively it uses QNX 8.0;
   real engineering effort; working non-trivial implementation that genuinely builds
   for or runs on QNX.
   Our answer: resource manager exposing PLC tags as files, native message passing
   with pulses, priority-inheritance protected tag store, SCHED_FIFO control loop,
   measured latency/jitter under CPU load.

2. **Design** - complete, coherent product experience, not just a technical PoC.
   Our answer: Unix philosophy (PLC tag = file; cat/echo/shell scripts work out of
   the box), config-driven deployment, uabridge-top monitoring, clean recovery
   behavior, reproducible build+run docs.

3. **Potential Impact** - credible, specific case for solving a real problem in a
   market QNX serves; why an RTOS foundation is the right choice.
   Our answer: industrial automation runs on OPC UA PLCs; QNX is strong in robotics/
   medical/industrial control; the missing bridge is a years-old open request
   (open62541 issues #339 #493 #594 #787 #5986, all closed unsatisfied before
   PR #8702 landed 2026-11-10). Determinism argument: control loops must not miss
   deadlines when the network stack is busy - pulses + priorities deliver that.

4. **Innovation & AI Creativity** - creative, non-obvious use of QNX; genuine
   understanding of the problem space.
   Our answer: turning an industrial protocol into QNX-native IPC (not another
   gateway with a REST API); stretch: lightweight streaming anomaly detection with
   pulse-delivered alerts.

## Bonus prize: Best use of QNX-specific Technologies ($3,500)

Judges look for creative/impactful/sophisticated use of: native message passing,
resource managers, microkernel architecture, startup/boot customization, real-time
services, security policies. This project's core IS four of those. Track evidence
per API in docs/qnx-evidence.md as code lands.

## Bonus prize: Best Codelab/Tutorial ($3,500)

A codelab authored during the submission period teaching a task on/for QNX 8.0;
need not relate to the project. Optional Phase 4 deliverable: "Expose PLC tags as
files with a QNX resource manager" - we will have the material naturally.

## Category choice

Primary: Robotics & Medical (timing/safety/reliability critical - our strongest
story: measured determinism under load). Decision recorded in ADR-001.
