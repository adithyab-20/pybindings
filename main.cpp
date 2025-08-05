// Copyright (c) 2025 Adithya Balachandra
// This software is licensed under the MIT License. See the LICENSE file for
// details.

/**
 * @file main.cpp
 * @brief Demonstration program showcasing the AB Modules functionality.
 *
 * This program demonstrates the usage of Calculator, Logger, and Notifier
 * components working together to perform arithmetic operations with logging
 * and notification capabilities.
 */

#include <iostream>

#include "ab/calculator/Calculator.h"
#include "ab/logger/Logger.h"
#include "ab/notifier/Notifier.h"

int main() {
  std::cout << "=== AB Modules Demo ===\n";

  try {
    // Initialize components
    const ab::calculator::Calculator calc;
    ab::logger::Logger logger;
    constexpr int notification_threshold = 100;
    ab::notifier::Notifier notifier(
        notification_threshold); // Notify if result > 100

    // Perform calculations with logging
    logger.log("Starting calculations");

    constexpr int first_number = 15;
    constexpr int second_number = 8;
    std::cout << "Computing: " << first_number << " + " << second_number
              << '\n';
    int result = calc.add(first_number, second_number);
    logger.log("Addition completed");
    std::cout << "Result: " << result << '\n';

    // Check for notifications
    notifier.checkAndNotify(result);
    if (notifier.wasNotified()) {
      std::cout << "Notification: Result exceeded threshold!\n";
    }

    // Demonstrate multiplication
    std::cout << "\nComputing: " << first_number << " * " << second_number
              << '\n';
    result = calc.multiply(first_number, second_number);
    logger.log("Multiplication completed");
    std::cout << "Result: " << result << '\n';

    notifier.checkAndNotify(result);
    if (notifier.wasNotified()) {
      std::cout << "Notification: Result exceeded threshold!\n";
    }

    // Display all logs
    std::cout << "\n=== Operation Log ===\n";
    const auto &logs = logger.getLogs();
    for (const auto &log : logs) {
      std::cout << "- " << log << '\n';
    }

    std::cout << "\n=== Demo Complete ===\n";

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }

  return 0;
}
