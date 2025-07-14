# Build the unit test for the Notifier component.
add_executable(unit_test_notifier test_notifier.cpp)
target_link_libraries(unit_test_notifier
  PRIVATE
    notifier
    GTest::gtest
    GTest::gtest_main
)

enable_coverage(unit_test_notifier)
include(GoogleTest)
gtest_discover_tests(unit_test_notifier)