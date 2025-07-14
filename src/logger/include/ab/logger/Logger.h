#ifndef AB_LOGGER_LOGGER_H_
#define AB_LOGGER_LOGGER_H_

#include <string>
#include <vector>

namespace ab::logger {

/**
 * @brief Records and retrieves log messages.
 */
class Logger {
public:
  /**
   * @brief Logs an operation message.
   * @param operation A C-string describing the operation.
   */
  void log(const char *operation);

  /**
   * @brief Retrieves all logged messages.
   * @return A constant reference to the log messages.
   */
  [[nodiscard]] const std::vector<std::string> &getLogs() const;

private:
  std::vector<std::string> logs_;
};

} // namespace ab::logger
#endif // AB_LOGGER_LOGGER_H_
