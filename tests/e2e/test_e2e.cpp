#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "ab/calculator/Calculator.h"
#include "ab/logger/Logger.h"
#include "ab/notifier/Notifier.h"

TEST(EndToEndTest, FullWorkflow) {
  // Instantiate components with proper namespace usage.
  const ab::calculator::Calculator calc;
  ab::logger::Logger logger;
  ab::notifier::Notifier notifier(10); // Threshold is 10

  // Perform calculations.
  int const result1 = calc.add(5, 6);      // Expected: 11
  int const result2 = calc.multiply(2, 3); // Expected: 6

  // Log operations.
  logger.log("Addition: 5 + 6");
  logger.log("Multiplication: 2 * 3");

  // Check notifications.
  notifier.checkAndNotify(result1); // Should trigger notification.
  notifier.checkAndNotify(result2); // Should not alter notification status.

  // Verify calculations.
  EXPECT_EQ(result1, 11);
  EXPECT_EQ(result2, 6);

  // Verify log contents.
  const std::vector<std::string> &logs = logger.getLogs();
  ASSERT_EQ(logs.size(), 2);
  EXPECT_EQ(logs[0], "Addition: 5 + 6");
  EXPECT_EQ(logs[1], "Multiplication: 2 * 3");

  // Verify that notification was triggered.
  EXPECT_TRUE(notifier.wasNotified());
}
