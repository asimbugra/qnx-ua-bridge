# ADR-003: Pinning open62541

Date: 2026-11-13
Status: accepted

## Context

The QNX 8.0 POSIX build fixes (PR #8702) merged to master on 2026-11-10
(merge commit 667acbc69132d3ba5b6db17be8002cb121849d41). The latest release
v1.5.10 (2026-10-30) PREDATES the merge: no release tag contains the fixes.

## Options

1. FetchContent pinned to merge commit 667acbc (or descendant)
2. FetchContent pinned to release tag v1.5.10 + carry local QNX patches
3. Git submodule

## Decision

**FetchContent pinned to 667acbc** (implemented in cmake/open62541.cmake).

## Consequences / rationale

- Option 2 means maintaining the very patches upstream just accepted - worse.
- Submodules complicate fresh clones for judges (rules: repo must be easy to
  reproduce); FetchContent fetches on configure.
- Client-only, subscriptions on, amalgamation off (small footprint, fast build).
- If a v1.5.11/v1.6 release appears before submission, retag to it and note in
  this ADR.
- Risk: master moves; pin insulates us. Revisit only if a release tag ships.
