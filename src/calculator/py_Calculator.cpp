#include <ab/calculator/Calculator.h>
#include <nanobind/nanobind.h>
#include <stdexcept>

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