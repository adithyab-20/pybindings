# Build the unit test for the Logger component.
add_executable(unit_test_logger test_logger.cpp)
target_link_libraries(unit_test_logger
  PRIVATE
    logger
    GTest::gtest
    GTest::gtest_main
)

enable_coverage(unit_test_logger)
include(GoogleTest)
gtest_discover_tests(unit_test_logger)