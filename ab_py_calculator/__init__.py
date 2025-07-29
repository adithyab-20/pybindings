"""
AB Calculator Python Bindings

Python bindings for the AB Calculator C++ library using nanobind.
"""

try:
    from ab_py_calculator.ab_calculator import Calculator
except ImportError as e:
    raise ImportError(f"Failed to import ab_calculator extension: {e}") from e

__version__ = "0.1.0"
__all__ = ["Calculator"]
