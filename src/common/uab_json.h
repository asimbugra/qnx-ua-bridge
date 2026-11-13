/*
 * JSON config parser wrapper (jsmn-based).
 * MIT license via jsmn.
 */
#ifndef UAB_JSON_H
#define UAB_JSON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* Opaque forward for jsmn tokens */
typedef struct jsmn_parser jsmn_parser;
typedef struct jsmntok jsmntok_t;

/* Our config structures mirror tags.example.json */
typedef enum {
    UAB_TAG_TYPE_DOUBLE = 0,
    UAB_TAG_TYPE_FLOAT,
    UAB_TAG_TYPE_INT32,
    UAB_TAG_TYPE_UINT32,
    UAB_TAG_TYPE_INT16,
    UAB_TAG_TYPE_UINT16,
    UAB_TAG_TYPE_BOOL,
    UAB_TAG_TYPE_STRING,
} uab_tag_type_e;

typedef enum {
    UAB_TAG_ACCESS_READ = 1,
    UAB_TAG_ACCESS_WRITE = 2,
    UAB_TAG_ACCESS_READWRITE = 3,
} uab_tag_access_e;

typedef struct {
    char path[128];                 /* e.g. "line1/conveyor_speed" */
    char node_id[256];              /* e.g. "ns=3;s="ConveyorDB".Speed" */
    uab_tag_type_e type;
    uab_tag_access_e access;
    int sampling_interval_ms;       /* 0 = default */
    double deadband;                /* 0.0 = no deadband */
} uab_tag_cfg_t;

typedef struct {
    char url[256];
    char security[32];              /* "none" or "Basic256Sha256" */
    int reconnect_min_ms;
    int reconnect_max_ms;
} uab_server_cfg_t;

typedef struct {
    uab_server_cfg_t server;
    uab_tag_cfg_t *tags;
    int tag_count;
    int tag_capacity;
} uab_config_t;

/* Parse JSON file into uab_config_t (allocates tags array).
 * Returns 0 on success, negative error code on failure.
 * Caller must call uab_config_free() when done.
 */
int uab_config_parse_file(const char *path, uab_config_t *out);
int uab_config_parse_string(const char *json, size_t len, uab_config_t *out);
void uab_config_free(uab_config_t *cfg);

/* Helper to find token by string key in object */
const jsmntok_t *uab_json_find_tok(const jsmntok_t *tokens, int count,
                                   const char *js, const char *key);
/* Get token value as string (null-terminated copy, caller frees) */
char *uab_json_tok_to_string(const jsmntok_t *tok, const char *js);
/* Get token value as double */
int uab_json_tok_to_double(const jsmntok_t *tok, const char *js, double *out);
/* Get token value as int */
int uab_json_tok_to_int(const jsmntok_t *tok, const char *js, int *out);
/* Get token value as bool */
int uab_json_tok_to_bool(const jsmntok_t *tok, const char *js, bool *out);

#endif /* UAB_JSON_H */
