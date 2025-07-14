/**
 * @file Logger.cpp
 * @brief Implementation of the Logger class for recording operation messages.
 *
 * This file contains the implementation of the Logger class, which provides
 * functionality to record and retrieve log messages for debugging and
 * monitoring purposes.
 */

#include <ab/logger/Logger.h>

#include <string>
#include <vector>

namespace ab::logger {

void Logger::log(const char *operation) {
  // Add the operation message to the internal log storage
  logs_.emplace_back(operation);
}

const std::vector<std::string> &Logger::getLogs() const {
  // Return a constant reference to the log collection
  return logs_;
}

} // namespace ab::logger