# open62541 on QNX - current state

All facts below verified against the GitHub API on 2026-11-13.

## PR #8702 - "fix(arch): build the POSIX architecture on QNX 8.0"

- URL: https://github.com/open62541/open62541/pull/8702
- Merged: 2026-11-10 22:21 UTC into master
- Merge commit: 667acbc69132d3ba5b6db17be8002cb121849d41 (verified on master)
- Size: 4 files, +17/-4
- Files and what they do:
  1. `arch/posix/eventloop_posix.h` - under `__QNX__`, include `<sys/queue.h>`
     instead of the bundled `open62541_queue.h` ("QNX has its own queue.h, but
     since QNX 8.0 the network headers no longer include it").
  2. `arch/posix/posix.cmake` - on QNX: link `socket` (sockets live in libsocket),
     skip `pthread` (pthread + POSIX RT extensions are in libc), skip `rt`.
  3. `examples/CMakeLists.txt` + `examples/pubsub_realtime/...c` - example fixes.
- The PR body closes #6967.

## Release status - IMPORTANT

- Latest release: **v1.5.10 (2026-10-30)** - BEFORE the QNX merge.
- The QNX fixes are on master only; **no release tag contains them yet**.
- Consequence: we must pin a master commit, not a release tag. Merge commit
  667acbc... or a slightly newer master commit that includes it.
  (master HEAD seen 2026-11-12: a1528c7a.)

## Prior QNX history

- Issues #339 (2015-era), #493, #594, #787, #5986 "Build for QNX" - all closed;
  years of unanswered demand before #8702.
- Earlier PRs #995 (QNX 6.5 config), #6966/#6967 (2025 QNX build support) were
  closed without merging; #8702 is the first QNX support to land upstream.

## What this means for the bridge

- Client-side usage (our case) is the well-trodden path of the POSIX architecture;
  the fixes cover exactly the POSIX arch build on QNX 8.0.
- PubSub RT examples were also fixed, indicating the maintainers care about QNX RT
  use cases - good sign for our story.
- Still Tier 3 / not CI-tested on QNX: expect rough edges; log every build issue
  in lessons-learned.md and keep any local patches as a documented layer.
