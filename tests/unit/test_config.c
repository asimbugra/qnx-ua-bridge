/*
 * Unit tests for config parsing (will use jsmn when integrated)
 */
#include "unity.h"
#include <stdio.h>

void test_config_smoke(void) {
    // Placeholder - real tests when parser exists
    TEST_ASSERT_EQUAL_INT(1, 1);
}

int main(void) {
    RUN_TEST(test_config_smoke);
    return UnityTestsFailed;
}
