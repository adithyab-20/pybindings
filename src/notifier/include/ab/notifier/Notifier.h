#pragma once

namespace ab::notifier {

/**
 * @brief Monitors results and triggers a notification when a threshold is
 * exceeded.
 */
class Notifier {
 public:
  /**
   * @brief Constructs a Notifier with a specified threshold.
   * @param thresh The threshold value for triggering notifications.
   */
  explicit Notifier(int thresh);

  /**
   * @brief Checks the given result and triggers a notification if it exceeds
   * the threshold.
   * @param result The result to check.
   */
  void checkAndNotify(int result);

  /**
   * @brief Indicates whether a notification was triggered.
   * @return True if a notification was triggered; otherwise, false.
   */
  [[nodiscard]] bool wasNotified() const;

 private:
  int threshold;
  bool notified{false};
};

} // namespace ab::notifier
