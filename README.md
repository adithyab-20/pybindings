# PyBindings - C++ Calculator with Python Interface

A calculator with C++ core and Python bindings using nanobind and scikit-build-core.

## Quick Start

### Prerequisites
- CMake, Ninja, Clang/LLVM
- Python 3.12+ with uv

### Build & Install

```bash
# Clone with submodules
git clone --recurse-submodules <repo-url>
cd pybindings

# Bootstrap vcpkg
cd vcpkg && ./bootstrap-vcpkg.sh && cd ..

# Build C++ components
cmake -B build -S . \
  -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DCMAKE_CXX_COMPILER=clang++ \
  -G Ninja
ninja -C build

# Install Python package (from ab_py_calculator directory)
cd ab_py_calculator
uv pip install -e ".[dev]"
```

### Usage

```python
from ab_py_calculator import Calculator
from ab_py_calculator.ab_calculator import InvalidArgument

calc = Calculator()

# Basic operations
result = calc.add(5, 3)         # 8
result = calc.subtract(10, 4)   # 6
result = calc.multiply(7, 6)    # 42
result = calc.divide(15, 3)     # 5

# Exception handling
try:
    calc.divide(10, 0)
except InvalidArgument as e:
    print("Division by zero error")
```

## Development

```bash
# Navigate to Python package directory
cd ab_py_calculator

# Run tests
uv run pytest

# Type checking
uv run mypy .

# Linting
uv run ruff check .

# Run example
uv run python example.py
```

## Build System

- **Backend**: scikit-build-core with nanobind
- **C++ Integration**: CMake with vcpkg package management
- **Python Package**: `ab-py-calculator` with proper type stubs

## License

MIT License - see LICENSE file.