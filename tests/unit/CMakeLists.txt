# Host unit tests
add_executable(test_config test_config.c framework/unity.c)
target_include_directories(test_config PRIVATE framework)
add_test(NAME config_tests COMMAND test_config)

add_executable(test_json test_json.c framework/unity.c ../../src/common/uab_json.c)
target_include_directories(test_json PRIVATE framework ../../src/common ../../vendor/jsmn)
add_test(NAME json_tests COMMAND test_json)
