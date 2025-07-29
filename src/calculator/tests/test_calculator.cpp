/**
 * @file test_calculator.cpp
 * @brief Unit tests for the Calculator class.
 *
 * This file contains comprehensive unit tests for the Calculator class,
 * testing all arithmetic operations including edge cases and error
 * conditions using Google Test framework.
 */

#include <ab/calculator/Calculator.h>
#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

TEST(CalculatorTest, BasicOperations) {
  const ab::calculator::Calculator calc;
  EXPECT_EQ(calc.add(2, 3), 5);
  EXPECT_EQ(calc.subtract(5, 3), 2);
  EXPECT_EQ(calc.multiply(4, 3), 12);
  EXPECT_EQ(calc.divide(10, 2), 5);
}

TEST(CalculatorTest, DivisionByZeroThrows) {
  const ab::calculator::Calculator calc;
  EXPECT_THROW({ calc.divide(10, 0); }, std::invalid_argument);
}

TEST(CalculatorTest, DivisionByNonZero) {
  const ab::calculator::Calculator calc;
  EXPECT_EQ(calc.divide(10, 2), 5);
  EXPECT_EQ(calc.divide(10, 5), 2);
}
