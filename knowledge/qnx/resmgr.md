# Resource manager patterns

Facts from QNX 8.0 docs (getting started + system security guide), verified 2026-11-13.

## Skeleton (dispatch framework)

```c
dispatch_t *dpp = dispatch_create_channel(-1, DISPATCH_FLAG_NOLOCK);
resmgr_attr_t resmgr_attr = { .nparts_max = 1, .msg_max_size = 2048 };
resmgr_connect_funcs_t connect_func; resmgr_io_funcs_t io_func;
iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &connect_func,
                 _RESMGR_IO_NFUNCS, &io_func);   // POSIX defaults
iofunc_attr_t attr;
iofunc_attr_init(&attr, S_IFNAM | 0666, 0, 0);
resmgr_attach(dpp, &resmgr_attr, "/dev/mynull", _FTYPE_ANY, 0,
              &connect_func, &io_func, &attr);
dispatch_context_t *ctp = dispatch_context_alloc(dpp);
while (1) { ctp = dispatch_block(ctp); dispatch_handler(ctp); }
```

- Override individual handlers AFTER iofunc_func_init: `io_func.io_read = my_io_read;`
- Multiple devices = multiple resmgr_attach calls, each with its own attr struct.
- iofunc_func_init fills connect+io tables with POSIX-layer defaults; override only
  what we need (read/write/readdir/stat later).

## Directory-like trees

- `_RESMGR_FLAG_DIR` on resmgr_attach makes the path a directory entry point (for
  /dev/opcua/<group>/<tag> trees). (Documented in resmgr_attach flags; verify
  exact readdir override details when implementing - confidence: documented.)

## Security note (8.0-specific)

- QNX recommends `secpol_resmgr_attach()` over plain resmgr_attach() when running
  under a security policy. For our dev/demo image the plain call is fine; keep in
  mind for the security story (bonus criterion mentions security policies).
  Source: System Security Guide, "Writing a resource manager".

## Pitfalls (to extend as we hit them)

- Blocking handlers stall the whole dispatch loop -> use thread pool
  (resmgr_attr + thread_pool_attach) for blocking ops.
- Always handle _IO_CONNECT + unblock pulses correctly (defaults usually cover).
