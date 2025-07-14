/**
 * @file Notifier.cpp
 * @brief Implementation of the Notifier class for threshold-based
 * notifications.
 *
 * This file contains the implementation of the Notifier class, which monitors
 * results and triggers notifications when specified thresholds are exceeded.
 */

#include <ab/notifier/Notifier.h>

namespace ab::notifier {

Notifier::Notifier(int thresh) : threshold(thresh) {
  // Initialize the notifier with the specified threshold value
  // The notified flag is default-initialized to false
}

void Notifier::checkAndNotify(int result) {
  // Check if the result exceeds the configured threshold
  if (result > threshold) {
    // Set the notification flag to indicate threshold exceeded
    notified = true;
  }
}

bool Notifier::wasNotified() const {
  // Return the current state of the notification flag
  return notified;
}

} // namespace ab::notifier