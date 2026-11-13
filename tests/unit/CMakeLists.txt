# Host unit tests
add_executable(test_config test_config.c framework/unity.c)
target_include_directories(test_config PRIVATE framework)
add_test(NAME config_tests COMMAND test_config)
