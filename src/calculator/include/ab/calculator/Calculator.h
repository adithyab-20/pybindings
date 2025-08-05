#ifndef AB_CALCULATOR_CALCULATOR_H_
#define AB_CALCULATOR_CALCULATOR_H_

#include <memory>

namespace ab::calculator {

/**
 * @brief Provides basic arithmetic operations using PIMPL pattern.
 *
 * This class demonstrates the PIMPL (Pointer to Implementation) idiom,
 * which provides compilation firewall and ABI stability.
 */
class Calculator {
 public:
  /**
   * @brief Default constructor.
   */
  Calculator();

  /**
   * @brief Destructor.
   */
  ~Calculator();

  /**
   * @brief Copy constructor.
   */
  Calculator(const Calculator& other);

  /**
   * @brief Copy assignment operator.
   */
  Calculator& operator=(const Calculator& other);

  /**
   * @brief Move constructor.
   */
  Calculator(Calculator&& other) noexcept;

  /**
   * @brief Move assignment operator.
   */
  Calculator& operator=(Calculator&& other) noexcept;

  /**
   * @brief Adds two integers.
   * @param lhs The first operand.
   * @param rhs The second operand.
   * @return The sum of the two operands.
   */
  [[nodiscard]] int add(int lhs, int rhs) const;

  /**
   * @brief Subtracts the second integer from the first.
   * @param lhs The first operand.
   * @param rhs The second operand.
   * @return The difference between the two operands.
   */
  [[nodiscard]] int subtract(int lhs, int rhs) const;

  /**
   * @brief Multiplies two integers.
   * @param lhs The first operand.
   * @param rhs The second operand.
   * @return The product of the two operands.
   */
  [[nodiscard]] int multiply(int lhs, int rhs) const;

  /**
   * @brief Divides one integer by another.
   * @param lhs The numerator.
   * @param rhs The divisor.
   * @return The quotient of the two operands.
   * @throws std::invalid_argument if the divisor is zero.
   */
  [[nodiscard]] int divide(int lhs, int rhs) const;

 private:
  struct Impl;
  std::unique_ptr<Impl> pimpl_;
};

} // namespace ab::calculator
#endif // AB_CALCULATOR_CALCULATOR_H_
