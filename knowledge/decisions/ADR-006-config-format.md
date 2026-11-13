# ADR-006: Tag configuration format

Date: 2026-11-13
Status: accepted

## Context

The bridge needs a static tag map (path -> node id, type, access, sampling) the
user edits by hand and tools/tagmap-gen generates. Parser must cross-compile for
QNX with minimal dependency surface (hackathon judges clone and build fresh).

## Options

1. YAML + libyaml - human friendly, but another cross-compiled dependency
2. JSON + jsmn (MIT, ~300 LOC, header-friendly) - tiny, zero deps beyond vendor
3. Custom INI-like - zero deps, but hand-rolled parser = avoidable bug surface

## Decision

**JSON with vendored jsmn** (third-party/ subdirectory, MIT license kept).

## Consequences

- config/tags.example.yaml migrates to config/tags.example.json (done with this
  ADR); tagmap-gen emits JSON.
- No YAML indentation surprises for generated files; shell-friendly.
- Comments: none in JSON - document fields in docs/ instead (accepted tradeoff).
- If hand-editing proves painful during Phase 1, tagmap-gen output stays JSON
  while a thin YAML->JSON converter runs on the host only (revisit then).
