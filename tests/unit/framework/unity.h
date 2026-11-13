/*
 * Unity - minimal unit test framework for C
 * Public domain (https://github.com/ThrowTheSwitch/Unity)
 * Only the parts we need for host unit tests.
 */
#ifndef UNITY_H
#define UNITY_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define UNITY_UINT uint32_t
#define UNITY_INT  int32_t
#define UNITY_UINT64 uint64_t
#define UNITY_INT64 int64_t

extern int UnityTestsFailed;
extern const char* UnityCurrentTestName;

void UnityBegin(const char* name);
void UnityEnd(void);
void UnityAssertEqualNumber(const char* msg, UNITY_INT expected, UNITY_INT actual, const char* file, int line);
void UnityAssertEqualString(const char* msg, const char* expected, const char* actual, const char* file, int line);
void UnityAssertNull(const char* msg, const void* ptr, const char* file, int line);
void UnityAssertNotNull(const char* msg, const void* ptr, const char* file, int line);
void UnityAssertNotEqualNumber(const char* msg, UNITY_INT expected, UNITY_INT actual, const char* file, int line);

#define TEST_ASSERT_EQUAL_INT(expected, actual) UnityAssertEqualNumber(NULL, (UNITY_INT)(expected), (UNITY_INT)(actual), __FILE__, __LINE__)
#define TEST_ASSERT_EQUAL_STRING(expected, actual) UnityAssertEqualString(NULL, expected, actual, __FILE__, __LINE__)
#define TEST_ASSERT_NULL(ptr) UnityAssertNull(NULL, ptr, __FILE__, __LINE__)
#define TEST_ASSERT_NOT_NULL(ptr) UnityAssertNotNull(NULL, ptr, __FILE__, __LINE__)
#define TEST_ASSERT_NOT_EQUAL(expected, actual) UnityAssertNotEqualNumber(NULL, (UNITY_INT)(expected), (UNITY_INT)(actual), __FILE__, __LINE__)
#define TEST_FAIL(msg) do { UnityAssertEqualNumber(msg, 1, 0, __FILE__, __LINE__); } while(0)

#define RUN_TEST(test_func) do { UnityBegin(#test_func); test_func(); UnityEnd(); } while(0)

#endif
