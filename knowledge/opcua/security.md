# OPC UA security on QNX 8.0

## Crypto availability on QNX 8.0 (verified from QNX docs, 2026-11-13)

- QNX SDP 8.0 ships **OpenSSL 3.0 LTS** (also 3.5): `libcrypto.so.3`, `libssl.so.3`,
  plus the qcrypto shim (`qcrypto-openssl-3.so`).
  Sources: QNX System Security Guide (qcrypto OpenSSL plugin page); SDP migration
  guide ("OpenSSL versions 3.0 (default) and 3.5 ship with QNX SDP 8.0"); GA release
  notes (Security section).
- Consequence: open62541's OpenSSL encryption backend
  (`UA_ENABLE_ENCRYPTION=OPENSSL`) is the natural choice on QNX 8.0 - no need to
  cross-compile mbedTLS ourselves. Final call in ADR (Phase 0/3).

## Plan

- Phase 1 MVP: `securityMode NONE` / `Basic128Rsa15` not needed - plain TCP.
- Phase 3: `Basic256Sha256` SignAndEncrypt against plc-sim with self-signed certs
  (open62541 ships cert generation tools). Upstream has NOT tested crypto on QNX;
  making it work and documenting it is a genuine contribution.

## Certificate handling

- Client certificate + key on target; trust list directory for the server cert.
- Never commit certs/keys - add to .gitignore; generate via scripts.
