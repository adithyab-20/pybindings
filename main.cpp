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

#include <ab/calculator/Calculator.h>
#include <ab/logger/Logger.h>
#include <ab/notifier/Notifier.h>

#include <iostream>
#include <stdexcept>

int main() {
  std::cout << "=== AB Modules Demo ===" << std::endl;

  try {
    // Initialize components
    ab::calculator::Calculator calc;
    ab::logger::Logger logger;
    constexpr int notification_threshold = 100;
    ab::notifier::Notifier notifier(
        notification_threshold); // Notify if result > 100

    // Perform calculations with logging
    logger.log("Starting calculations");

    constexpr int first_number = 15;
    constexpr int second_number = 8;
    std::cout << "Computing: " << first_number << " + " << second_number
              << std::endl;
    int result = calc.add(first_number, second_number);
    logger.log("Addition completed");
    std::cout << "Result: " << result << std::endl;

    // Check for notifications
    notifier.checkAndNotify(result);
    if (notifier.wasNotified()) {
      std::cout << "Notification: Result exceeded threshold!" << std::endl;
    }

    // Demonstrate multiplication
    std::cout << "\nComputing: " << first_number << " * " << second_number
              << std::endl;
    result = calc.multiply(first_number, second_number);
    logger.log("Multiplication completed");
    std::cout << "Result: " << result << std::endl;

    notifier.checkAndNotify(result);
    if (notifier.wasNotified()) {
      std::cout << "Notification: Result exceeded threshold!" << std::endl;
    }

    // Display all logs
    std::cout << "\n=== Operation Log ===" << std::endl;
    const auto &logs = logger.getLogs();
    for (const auto &log : logs) {
      std::cout << "- " << log << std::endl;
    }

    std::cout << "\n=== Demo Complete ===" << std::endl;

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
