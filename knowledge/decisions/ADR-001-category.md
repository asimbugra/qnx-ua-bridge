# ADR-001: Hackathon category

Date: 2026-11-13
Status: accepted

## Context

The rules require exactly one category: Robotics & Medical, Automotive & Mobility,
Low-level Software, Developer Tooling & Host Tools, Open-Source Contribution & Ports.
Each category has a $4,000 best-of + $2,000 runner-up.

## Options

1. Robotics & Medical - "real-time applications where timing, safety, or reliability
   is critical"
2. Developer Tooling & Host Tools - host-side tools that support QNX development
3. Open-Source Contribution & Ports - porting existing OSS to QNX

## Decision

**Robotics & Medical.**

## Consequences / rationale

- Our strongest, most honest story: measured determinism (latency/jitter under CPU
  load), control loop stability, recovery behavior - all squarely "timing, safety,
  reliability".
- Category 3 fits ("port of open62541") but the rules for it demand a porting-layer
  repo and it frames us as a porter, not a builder; our value is the bridge product.
- Category 2 undersells the target-side work (resmgr, message passing).
- Bonus prize "Best use of QNX-specific Technologies" is orthogonal to category and
  remains a target regardless.
