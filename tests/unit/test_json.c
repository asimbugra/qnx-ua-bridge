/*
 * Unit tests for JSON config parser
 */
#include "unity.h"
#include "uab_json.h"
#include <stdio.h>
#include <string.h>

static const char *valid_json =
    "{"
    "  \"server\": {"
    "    \"url\": \"opc.tcp://localhost:4840\","
    "    \"security\": \"none\","
    "    \"reconnect_min_ms\": 500,"
    "    \"reconnect_max_ms\": 30000"
    "  },"
    "  \"tags\": ["
    "    {\"path\": \"line1/speed\", \"node_id\": \"ns=3;s=DB.Speed\", \"type\": \"double\", \"access\": \"read\", \"sampling_interval_ms\": 100, \"deadband\": 0.0},"
    "    {\"path\": \"line1/setpoint\", \"node_id\": \"ns=3;s=DB.Setpoint\", \"type\": \"double\", \"access\": \"write\"}"
    "  ]"
    "}";

void test_parse_valid_config(void) {
    uab_config_t cfg;
    int r = uab_config_parse_string(valid_json, strlen(valid_json), &cfg);
    TEST_ASSERT_EQUAL_INT(0, r);
    TEST_ASSERT_EQUAL_STRING("opc.tcp://localhost:4840", cfg.server.url);
    TEST_ASSERT_EQUAL_STRING("none", cfg.server.security);
    TEST_ASSERT_EQUAL_INT(500, cfg.server.reconnect_min_ms);
    TEST_ASSERT_EQUAL_INT(30000, cfg.server.reconnect_max_ms);
    TEST_ASSERT_EQUAL_INT(2, cfg.tag_count);
    if (cfg.tag_count >= 1) {
        TEST_ASSERT_EQUAL_STRING("line1/speed", cfg.tags[0].path);
        TEST_ASSERT_EQUAL_STRING("ns=3;s=DB.Speed", cfg.tags[0].node_id);
        TEST_ASSERT_EQUAL_INT(UAB_TAG_TYPE_DOUBLE, cfg.tags[0].type);
        TEST_ASSERT_EQUAL_INT(UAB_TAG_ACCESS_READ, cfg.tags[0].access);
        TEST_ASSERT_EQUAL_INT(100, cfg.tags[0].sampling_interval_ms);
    }
    if (cfg.tag_count >= 2) {
        TEST_ASSERT_EQUAL_STRING("line1/setpoint", cfg.tags[1].path);
        TEST_ASSERT_EQUAL_INT(UAB_TAG_ACCESS_WRITE, cfg.tags[1].access);
        TEST_ASSERT_EQUAL_INT(0, cfg.tags[1].sampling_interval_ms);
    }
    uab_config_free(&cfg);
}

void test_parse_missing_server(void) {
    const char *bad = "{\"tags\":[]}";
    uab_config_t cfg;
    int r = uab_config_parse_string(bad, strlen(bad), &cfg);
    TEST_ASSERT_NOT_EQUAL(0, r);
}

void test_parse_example_file(void) {
    uab_config_t cfg;
    /* Relative to repo root when ctest runs from build dir */
    int r = uab_config_parse_file("../../config/tags.example.json", &cfg);
    if (r == 0) {
        TEST_ASSERT_EQUAL_INT(3, cfg.tag_count);
        uab_config_free(&cfg);
    } else {
        /* path depends on cwd; not an error */
        printf("example file not reachable from cwd, skipped\n");
    }
}

int main(void) {
    RUN_TEST(test_parse_valid_config);
    RUN_TEST(test_parse_missing_server);
    RUN_TEST(test_parse_example_file);
    return UnityTestsFailed;
}
