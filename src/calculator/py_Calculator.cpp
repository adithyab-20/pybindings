/**
 * @file py_Calculator.cpp
 * @brief Python bindings for the Calculator class using nanobind.
 *
 * This file contains the nanobind module definition that exposes the
 * Calculator C++ class to Python, providing a clean Python interface
 * for calculator operations with exception handling.
 */

#include <stdexcept>

#include <nanobind/nanobind.h>

#include "ab/calculator/Calculator.h"

namespace nb = nanobind;
using namespace nb::literals;

NB_MODULE(ab_calculator, m) {
  m.doc() = "Python bindings for AB Calculator component";

  nb::class_<ab::calculator::Calculator>(m, "Calculator")
      .def(nb::init<>(), "Default constructor")
      .def("add", &ab::calculator::Calculator::add, "Add two integers", "lhs"_a,
           "rhs"_a)
      .def("subtract", &ab::calculator::Calculator::subtract,
           "Subtract second integer from first", "lhs"_a, "rhs"_a)
      .def("multiply", &ab::calculator::Calculator::multiply,
           "Multiply two integers", "lhs"_a, "rhs"_a)
      .def("divide", &ab::calculator::Calculator::divide,
           "Divide first integer by second (throws on division by zero)",
           "lhs"_a, "rhs"_a);

  nb::exception<std::invalid_argument>(m, "InvalidArgument");
}