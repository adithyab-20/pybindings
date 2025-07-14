# Build the unit test for the Calculator component.
add_executable(unit_test_calculator test_calculator.cpp)
target_link_libraries(unit_test_calculator
  PRIVATE
    calculator
    GTest::gtest
    GTest::gtest_main
)

enable_coverage(unit_test_calculator)
include(GoogleTest)
gtest_discover_tests(unit_test_calculator)