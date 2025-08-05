#include <gtest/gtest.h>

#include "ab/notifier/Notifier.h"

TEST(NotifierTest, CheckNotifications) {
  constexpr int threshold = 10;
  constexpr int value_below_threshold = 5;
  constexpr int value_above_threshold = 15;

  ab::notifier::Notifier notifier(threshold);

  notifier.checkAndNotify(value_below_threshold);
  EXPECT_FALSE(notifier.wasNotified());

  notifier.checkAndNotify(value_above_threshold);
  EXPECT_TRUE(notifier.wasNotified());
}
