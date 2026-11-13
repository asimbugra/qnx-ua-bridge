/*
 * JSON config parser implementation (jsmn).
 */
#include "uab_json.h"
#include "jsmn.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_TOKENS 256

static int parse_server(const jsmntok_t *tokens, int count, const char *js,
                        uab_server_cfg_t *out) {
    const jsmntok_t *t;
    t = uab_json_find_tok(tokens, count, js, "url");
    if (!t) return -1;
    char *s = uab_json_tok_to_string(t, js);
    if (!s) return -2;
    strncpy(out->url, s, sizeof(out->url) - 1);
    free(s);

    t = uab_json_find_tok(tokens, count, js, "security");
    if (t) {
        s = uab_json_tok_to_string(t, js);
        if (s) { strncpy(out->security, s, sizeof(out->security) - 1); free(s); }
    } else {
        strcpy(out->security, "none");
    }

    t = uab_json_find_tok(tokens, count, js, "reconnect_min_ms");
    if (t && uab_json_tok_to_int(t, js, &out->reconnect_min_ms) == 0) {}
    else out->reconnect_min_ms = 500;

    t = uab_json_find_tok(tokens, count, js, "reconnect_max_ms");
    if (t && uab_json_tok_to_int(t, js, &out->reconnect_max_ms) == 0) {}
    else out->reconnect_max_ms = 30000;
    return 0;
}

static int tag_type_from_string(const char *s) {
    if (!s) return UAB_TAG_TYPE_DOUBLE;
    if (strcmp(s, "double") == 0) return UAB_TAG_TYPE_DOUBLE;
    if (strcmp(s, "float") == 0) return UAB_TAG_TYPE_FLOAT;
    if (strcmp(s, "int32") == 0) return UAB_TAG_TYPE_INT32;
    if (strcmp(s, "uint32") == 0) return UAB_TAG_TYPE_UINT32;
    if (strcmp(s, "int16") == 0) return UAB_TAG_TYPE_INT16;
    if (strcmp(s, "uint16") == 0) return UAB_TAG_TYPE_UINT16;
    if (strcmp(s, "bool") == 0) return UAB_TAG_TYPE_BOOL;
    if (strcmp(s, "string") == 0) return UAB_TAG_TYPE_STRING;
    return UAB_TAG_TYPE_DOUBLE;
}

static int tag_access_from_string(const char *s) {
    if (!s) return UAB_TAG_ACCESS_READ;
    if (strcmp(s, "read") == 0) return UAB_TAG_ACCESS_READ;
    if (strcmp(s, "write") == 0) return UAB_TAG_ACCESS_WRITE;
    if (strcmp(s, "readwrite") == 0) return UAB_TAG_ACCESS_READWRITE;
    return UAB_TAG_ACCESS_READ;
}

static int parse_tags(const jsmntok_t *tokens, int count, const char *js,
                      uab_config_t *cfg) {
    const jsmntok_t *tags_arr = uab_json_find_tok(tokens, count, js, "tags");
    if (!tags_arr || tags_arr->type != JSMN_ARRAY) return -1;

    cfg->tag_capacity = tags_arr->size;
    cfg->tags = calloc(cfg->tag_capacity, sizeof(uab_tag_cfg_t));
    if (!cfg->tags) return -2;
    cfg->tag_count = 0;

    for (int i = 0; i < tags_arr->size; i++) {
        const jsmntok_t *tag_obj = &tokens[tags_arr->size == 0 ? 0 : 1 + i]; /* approximation - fix below */
    }

    /* jsmn doesn't give direct child array, need to walk tokens */
    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (tokens[i].start == tags_arr->start && tokens[i].end == tags_arr->end) {
            idx = i;
            break;
        }
    }
    if (idx < 0) return -3;

    /* Walk children of tags array */
    int child_start = idx + 1;
    int parsed = 0;
    for (int i = child_start; i < count && parsed < cfg->tag_capacity; i++) {
        if (tokens[i].type == JSMN_OBJECT) {
            uab_tag_cfg_t *tag = &cfg->tags[cfg->tag_count++];
            const jsmntok_t *t;

            t = uab_json_find_tok(&tokens[i], count - i, js, "path");
            if (t) { char *s = uab_json_tok_to_string(t, js); if (s) { strncpy(tag->path, s, sizeof(tag->path)-1); free(s); } }

            t = uab_json_find_tok(&tokens[i], count - i, js, "node_id");
            if (t) { char *s = uab_json_tok_to_string(t, js); if (s) { strncpy(tag->node_id, s, sizeof(tag->node_id)-1); free(s); } }

            t = uab_json_find_tok(&tokens[i], count - i, js, "type");
            if (t) { char *s = uab_json_tok_to_string(t, js); if (s) { tag->type = tag_type_from_string(s); free(s); } }

            t = uab_json_find_tok(&tokens[i], count - i, js, "access");
            if (t) { char *s = uab_json_tok_to_string(t, js); if (s) { tag->access = tag_access_from_string(s); free(s); } }

            t = uab_json_find_tok(&tokens[i], count - i, js, "sampling_interval_ms");
            if (t) { int v; if (uab_json_tok_to_int(t, js, &v) == 0) tag->sampling_interval_ms = v; }

            t = uab_json_find_tok(&tokens[i], count - i, js, "deadband");
            if (t) { double v; if (uab_json_tok_to_double(t, js, &v) == 0) tag->deadband = v; }

            parsed++;
        }
    }
    return 0;
}

int uab_config_parse_file(const char *path, uab_config_t *out) {
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(len + 1);
    if (!buf) { fclose(f); return -2; }
    fread(buf, 1, len, f);
    buf[len] = '\0';
    fclose(f);
    int r = uab_config_parse_string(buf, len, out);
    free(buf);
    return r;
}

int uab_config_parse_string(const char *json, size_t len, uab_config_t *out) {
    memset(out, 0, sizeof(*out));
    jsmn_parser parser;
    jsmn_init(&parser);
    jsmntok_t tokens[MAX_TOKENS];
    int r = jsmn_parse(&parser, json, len, tokens, MAX_TOKENS);
    if (r < 0) return r;
    if (r < 1 || tokens[0].type != JSMN_OBJECT) return -1;

    const jsmntok_t *server_obj = uab_json_find_tok(tokens, r, json, "server");
    if (!server_obj) return -2;
    if (parse_server(tokens, r, json, &out->server) < 0) return -3;
    if (parse_tags(tokens, r, json, out) < 0) return -4;
    return 0;
}

void uab_config_free(uab_config_t *cfg) {
    free(cfg->tags);
    cfg->tags = NULL;
    cfg->tag_count = cfg->tag_capacity = 0;
}

/* Token helpers */
const jsmntok_t *uab_json_find_tok(const jsmntok_t *tokens, int count,
                                   const char *js, const char *key) {
    if (!tokens || count < 1 || tokens[0].type != JSMN_OBJECT) return NULL;
    for (int i = 1; i < count; i++) {
        if (tokens[i].type == JSMN_STRING) {
            int klen = tokens[i].end - tokens[i].start;
            if (klen == (int)strlen(key) && strncmp(js + tokens[i].start, key, klen) == 0) {
                if (i + 1 < count) return &tokens[i + 1];
            }
        }
    }
    return NULL;
}

char *uab_json_tok_to_string(const jsmntok_t *tok, const char *js) {
    if (!tok || tok->type != JSMN_STRING) return NULL;
    int len = tok->end - tok->start;
    char *s = malloc(len + 1);
    if (!s) return NULL;
    memcpy(s, js + tok->start, len);
    s[len] = '\0';
    return s;
}

int uab_json_tok_to_double(const jsmntok_t *tok, const char *js, double *out) {
    if (!tok || tok->type != JSMN_PRIMITIVE) return -1;
    int len = tok->end - tok->start;
    char *s = malloc(len + 1);
    if (!s) return -2;
    memcpy(s, js + tok->start, len);
    s[len] = '\0';
    char *end;
    double v = strtod(s, &end);
    free(s);
    if (end == s) return -3;
    *out = v;
    return 0;
}

int uab_json_tok_to_int(const jsmntok_t *tok, const char *js, int *out) {
    if (!tok || tok->type != JSMN_PRIMITIVE) return -1;
    int len = tok->end - tok->start;
    char *s = malloc(len + 1);
    if (!s) return -2;
    memcpy(s, js + tok->start, len);
    s[len] = '\0';
    char *end;
    long v = strtol(s, &end, 10);
    free(s);
    if (end == s) return -3;
    *out = (int)v;
    return 0;
}

int uab_json_tok_to_bool(const jsmntok_t *tok, const char *js, bool *out) {
    if (!tok || tok->type != JSMN_PRIMITIVE) return -1;
    int len = tok->end - tok->start;
    if (len == 4 && strncmp(js + tok->start, "true", 4) == 0) { *out = true; return 0; }
    if (len == 5 && strncmp(js + tok->start, "false", 5) == 0) { *out = false; return 0; }
    return -2;
}
