/**
 * @file Calculator.cpp
 * @brief Implementation of the Calculator class for basic arithmetic
 * operations.
 *
 * This file contains the implementation of the Calculator class using the PIMPL
 * idiom for compilation firewall and ABI stability.
 */

#include "ab/calculator/Calculator.h"

#include <memory>
#include <stdexcept>

namespace ab::calculator {

// Implementation struct containing the actual logic
struct Calculator::Impl {
  [[nodiscard]] static int add(int lhs, int rhs) { return lhs + rhs; }

  [[nodiscard]] static int subtract(int lhs, int rhs) { return lhs - rhs; }

  [[nodiscard]] static int multiply(int lhs, int rhs) { return lhs * rhs; }

  [[nodiscard]] static int divide(int lhs, int rhs) {
    if (rhs == 0) {
      throw std::invalid_argument("Division by zero");
    }
    return lhs / rhs;
  }
};

// Constructor
Calculator::Calculator() : pimpl_(std::make_unique<Impl>()) {}

// Destructor
Calculator::~Calculator() = default;

// Copy constructor
Calculator::Calculator([[maybe_unused]] const Calculator& other)
    : pimpl_(std::make_unique<Impl>()) {}

// Copy assignment operator
Calculator& Calculator::operator=([[maybe_unused]] const Calculator& other) {
  if (this != &other) {
    pimpl_ = std::make_unique<Impl>();
  }
  return *this;
}

// Move constructor
Calculator::Calculator(Calculator&& other) noexcept = default;

// Move assignment operator
Calculator& Calculator::operator=(Calculator&& other) noexcept = default;

// Public interface methods - delegate to implementation
int Calculator::add(int lhs, int rhs) const { return Impl::add(lhs, rhs); }

int Calculator::subtract(int lhs, int rhs) const {
  return Impl::subtract(lhs, rhs);
}

int Calculator::multiply(int lhs, int rhs) const {
  return Impl::multiply(lhs, rhs);
}

int Calculator::divide(int lhs, int rhs) const {
  return Impl::divide(lhs, rhs);
}

} // namespace ab::calculator
