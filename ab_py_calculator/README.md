# AB Python Calculator

Python-C++ binding template using nanobind.

## Installation

```bash
# Development
uv pip install -e ".[dev]"

# Production
uv pip install ab-py-calculator
```

## Usage

```python
from ab_py_calculator import Calculator

# Create calculator
calc = Calculator()

# Operations
result = calc.add(5, 3)        # 8
result = calc.subtract(10, 4)  # 6
result = calc.multiply(3, 7)   # 21
result = calc.divide(15, 3)    # 5
```

## Development

```bash
# Testing
uv run pytest tests/

# Linting & Type Checking
uv run ruff check .
uv run mypy .
```

## Template Structure

This serves as a complete template for creating Python bindings for C++ libraries using:
- **nanobind** for efficient Python-C++ bindings
- **scikit-build-core** for modern Python packaging
- **CMake** for C++ build configuration

## Requirements

- Python 3.12+
- C++17 compiler
- nanobind