/*
 * Unity implementation (minimal subset)
 */
#include "unity.h"

int UnityTestsFailed = 0;
const char* UnityCurrentTestName = NULL;

void UnityBegin(const char* name) {
    UnityCurrentTestName = name;
    UnityTestsFailed = 0;
    printf("[RUN] %s\n", name);
}

void UnityEnd(void) {
    if (UnityTestsFailed == 0) {
        printf("[OK]  %s\n", UnityCurrentTestName);
    } else {
        printf("[FAIL] %s (%d failures)\n", UnityCurrentTestName, UnityTestsFailed);
    }
    UnityCurrentTestName = NULL;
}

void UnityAssertEqualNumber(const char* msg, UNITY_INT expected, UNITY_INT actual, const char* file, int line) {
    if (expected != actual) {
        UnityTestsFailed++;
        printf("  ASSERT_EQUAL failed at %s:%d: expected %d, got %d%s%s\n",
               file, line, expected, actual, msg ? ": " : "", msg ? msg : "");
    }
}

void UnityAssertEqualString(const char* msg, const char* expected, const char* actual, const char* file, int line) {
    if (expected == NULL || actual == NULL || strcmp(expected, actual) != 0) {
        UnityTestsFailed++;
        printf("  ASSERT_EQUAL_STRING failed at %s:%d: expected '%s', got '%s'%s%s\n",
               file, line, expected ? expected : "(null)", actual ? actual : "(null)",
               msg ? ": " : "", msg ? msg : "");
    }
}

void UnityAssertNull(const char* msg, const void* ptr, const char* file, int line) {
    if (ptr != NULL) {
        UnityTestsFailed++;
        printf("  ASSERT_NULL failed at %s:%d: got %p%s%s\n",
               file, line, ptr, msg ? ": " : "", msg ? msg : "");
    }
}

void UnityAssertNotNull(const char* msg, const void* ptr, const char* file, int line) {
    if (ptr == NULL) {
        UnityTestsFailed++;
        printf("  ASSERT_NOT_NULL failed at %s:%d%s%s\n",
               file, line, msg ? ": " : "", msg ? msg : "");
    }
}

void UnityAssertNotEqualNumber(const char* msg, UNITY_INT expected, UNITY_INT actual, const char* file, int line) {
    if (expected == actual) {
        UnityTestsFailed++;
        printf("  ASSERT_NOT_EQUAL failed at %s:%d: both are %d%s%s\n",
               file, line, (int)expected, msg ? ": " : "", msg ? msg : "");
    }
}
