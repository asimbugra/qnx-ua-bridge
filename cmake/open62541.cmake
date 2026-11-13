# Fetch open62541 as a dependency at a pinned commit.
#
# The QNX 8.0 POSIX build fixes (PR #8702) landed upstream on 2026-11-10.
# The pin below is provisional until the exact merge SHA and the first
# release tag containing it are verified.
include(FetchContent)

FetchContent_Declare(
    open62541
    GIT_REPOSITORY https://github.com/open62541/open62541.git
    GIT_TAG        667acbc69132d3ba5b6db17be8002cb121849d41  # PR #8702 QNX 8.0 POSIX fixes (merged 2026-11-10); no release tag contains them yet
    GIT_SHALLOW    TRUE
)

# Client-only build; keep the footprint small.
set(UA_ENABLE_AMALGAMATION OFF CACHE BOOL "" FORCE)
set(UA_ENABLE_SUBSCRIPTIONS ON  CACHE BOOL "" FORCE)

# Wired up when the first target links against open62541:
# FetchContent_MakeAvailable(open62541)
