#include <ab/calculator/Calculator.h>
#include <ab/logger/Logger.h>

#include <gtest/gtest.h>

#include <string>
#include <vector>

class MockNotifier {
public:
  bool notified = false;

  // For this test, if result > 10, the notifier should trigger.
  void checkAndNotify(int result) {
    if (result > 10) {
      notified = true;
    }
  }
};

TEST(IntegrationTest, CalculatorLogger_MockNotifier) {
  // Create instances of Calculator and Logger.
  ab::calculator::Calculator const calc;
  ab::logger::Logger log;
  MockNotifier mockNotifier;

  // Perform a calculation that yields a result greater than 10.
  int const result = calc.add(8, 5); // Expected result: 13
  std::string const logMessage = "Addition: 8 + 5 = " + std::to_string(result);

  // Log the operation.
  log.log(logMessage.c_str());

  // Use the mock notifier to check the result.
  mockNotifier.checkAndNotify(result);

  // Verify the Logger captured the correct log message.
  const std::vector<std::string> &logs = log.getLogs();
  ASSERT_FALSE(logs.empty());
  EXPECT_EQ(logs.back(), logMessage);

  // Verify that the notifier was triggered.
  EXPECT_TRUE(mockNotifier.notified);
}