# ADR-002: License

Date: 2026-11-13
Status: accepted

## Context

Rules require an open-source license visible in the repo About section. open62541
is MPL-2.0. We fetch it as a pinned dependency via FetchContent; we do not
redistribute its source in our repo.

## Options

1. Apache-2.0 - permissive, patent grant, common for infrastructure
2. MIT - permissive, simplest
3. MPL-2.0 - match upstream

## Decision

**Apache-2.0** (already committed as LICENSE; GitHub detects it in About).

## Consequences / rationale

- MPL-2.0 is file-level copyleft: it applies to open62541's own files, which we only
  build and link, not include. Linking an MPL-2.0 library from Apache-2.0 code is
  the standard, permitted pattern (MPL-2.0 §3 explicitly allows larger works).
- Apache-2.0 adds an explicit patent grant over MIT, fitting an industrial bridge.
- No additional NOTICE obligations triggered since we ship no upstream files.
